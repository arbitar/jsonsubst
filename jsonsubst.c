#include <stdio.h>
#include <json-c/json.h>
#include <string.h>

#define MAX_NUM_KEYS 32

json_object* substitute_json_variable(json_object* json, char* token) {
  char* keys[MAX_NUM_KEYS];
  int num_keys = 0;
  char* key = strtok(token, ".");
  while (key != NULL && num_keys < MAX_NUM_KEYS) {
    keys[num_keys] = key;
    key = strtok(NULL, ".");
    num_keys++;
  }

  if (num_keys == 0) {
    return NULL;
  }

  json_object* value = json;
  for (int i = 0; i < num_keys; i++) {
    value = json_object_object_get(value, keys[i]);
    if (value == NULL) {
      return NULL;
    }
  }

  return value;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Error: No JSON file specified\n");
    return 1;
  }

  json_object* json = json_object_from_file(argv[1]);
  if (json == NULL) {
    fprintf(stderr, "Error: Failed to parse JSON file\n");
    return 1;
  }

  char* line = NULL;
  size_t line_size = 0;
  while (getline(&line, &line_size, stdin) > 0) {
    char* token = strstr(line, "{{ ");
    while (token != NULL) {
      char* end_token = strstr(token, " }}");
      if (end_token == NULL) {
        break;
      }

      size_t token_length = end_token - token - 3;

      char token_buffer[token_length];
      strncpy(token_buffer, token + 3, token_length);
      token_buffer[token_length] = '\0';

      json_object* value = substitute_json_variable(json, token_buffer);
      if (value == NULL) {
        fprintf(stderr, "Error: Invalid token: %s\n", token_buffer);
        return 1;
      }

      char* value_str = (char*)json_object_get_string(value);
      size_t value_str_length = strlen(value_str);
      memmove(token + value_str_length, end_token + 3, strlen(end_token + 3) + 1);
      memcpy(token, value_str, value_str_length);

      token = strstr(line, "{{ ");
    }

    printf("%s", line);
  }

  free(line);
  json_object_put(json);

  return 0;
}
