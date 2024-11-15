#include <ctype.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE (1024)
#define NUM_OF_KEYS (50)
#define NUM_OF_VALUES (100)
#define MAX_OBJECTS (256)
#define FILE_SIZE (15)

// function to parse the json
int get_json(char argcee, char runit[], char *argument_one[], char 
filename[FILE_SIZE]) 
{
        FILE *fp;

        strncpy(runit, argument_one[0], 10);
        strcat(runit, " ");
        char buffer[BUFF_SIZE];
        char stringed[BUFF_SIZE];
        struct json_object *parsed_json;
        int i, j = 0;
        int a = 0;
        int switched = 0;
        int arg = 0;
        int arg_len = 0;
        int comma = 0;

        char code[NUM_OF_KEYS][NUM_OF_VALUES];
        char arg_vals[NUM_OF_VALUES][BUFF_SIZE];

        fp = fopen(filename, "r");

        if (fp == NULL) {
                printf( "File does not exist!!!\n");

                return -1;
        }

        fread(buffer, BUFF_SIZE, 1, fp);
        fclose(fp);

        parsed_json = json_tokener_parse(buffer);
        strncpy(stringed, json_object_get_string(parsed_json),
                BUFF_SIZE);

        for (i = 0; i < BUFF_SIZE; i++) {

                if (stringed[i] == '[') {
                        switched = -1;
                }
                if (stringed[i] == ']' && stringed[i + 1] == ',') {
                        switched = 0;
                }

                if (stringed[i] != '"' && stringed[i] != ':' &&
                    stringed[i] != '{' && stringed[i] != '}') {
                        if (stringed[i] != '[' && stringed[i] != ']') {
                                if (switched == 0 &&
                                    stringed[i] != ',') {
                                        code[a][j] = stringed[i];
                                        j += 1;
                                }

                                else {
                                        if (stringed[i] == ',' && switched 
                                        == -1) {
                                                arg_vals[arg][arg_len]
                                                 = stringed[i];
                                                arg_len += 1;
                                        }
                                        if (stringed[i] != ',' && switched 
                                        != -1) {
                                                arg_vals[arg][arg_len] =
                                                    stringed[i];
                                                arg_len += 1;
                                        }
                                        if (stringed[i] != ',' && switched 
                                        == -1) {
                                                arg_vals[arg][arg_len] =
                                                    stringed[i];
                                                arg_len += 1;
                                        }
                                }
                        }
                }
                if (stringed[i] == ',' && switched != -1) {
                        a += 1;
                        j = 0;
                        arg_len = 0;
                        arg += 1;
                        switched = 0;
                        comma = 0;
                }
                if (stringed[i] == ':' && comma == 0) {
                        switched = 1;
                        comma = 1;
                }
                if (stringed[i] == '}') {
                        break;
                }
        }

        for (int i = 0; i < NUM_OF_KEYS; i++) {
                strcat(runit, code[i]);
                strcat(runit, arg_vals[i]);
        }

        return 0;
}