#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// Struct declarations
typedef struct
{
    char* buffer;
    size_t buffer_length;
    __ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer()
{
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

// Statement struct and enum declaration
typedef enum 
{
    STATEMENT_INSERT, 
    STATEMENT_SELECT
} StatementType;

typedef struct
{
    StatementType type;
} Statement;

// Enum declarations
typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

// Prints a prompt to the user. We do this before reading each line of input.
void print_prompt() { printf("shroom > "); }

// To read a line of input, use getline():
// ---------------------------------------
// ssize_t getline(char **lineptr, size_t *n, FILE *stream);
// lineptr : a pointer to the variable we use to point to the buffer containing the read line. If it set to NULL it is mallocatted by getline and should thus be freed by the user, even if the command fails.
// n : a pointer to the variable we use to save the size of allocated buffer.
// stream : the input stream to read from. We’ll be reading from standard input.
// return value : the number of bytes read, which may be less than the size of the buffer.
// ---------------------------------------
void read_input(InputBuffer* input_buffer)
{
    __ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

// Disposes of buffer data
void close_input_buffer(InputBuffer* input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

// A wrapper for existing functionality that leaves room for more commands
MetaCommandResult do_meta_command(InputBuffer* input_buffer)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        exit(EXIT_SUCCESS);
    } else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    } 
}

// Does not understand SQL right now. In fact, it only understands two words
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement)
{
    if (strncmp(input_buffer->buffer, "insert", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

// Actually executes the statement, only stubs now because no actual SQL gets inputed
// and no data yet
void execute_statement(Statement* statement)
{
    switch (statement->type)
    {
        case (STATEMENT_INSERT):
            printf("This is where we would do an insert.\n");
            break;
        case (STATEMENT_SELECT):
            printf("This is where we would do a select.\n");
            break;
    }
}

// Contains an infinite loop that prints the prompt, gets a line of input, then processes that line of input 
int main(int argc, char* argv[])
{
    InputBuffer* input_buffer = new_input_buffer();
    while (true)
    {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_command(input_buffer))
            {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'.\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }

        execute_statement(&statement);
    }
}
