#include <stdio.h>
#include <argp.h>
#include <toml.h>
const char *cdates_version = "cdates 0.1";
const char *cdates_bug_address = "<mdddmmmm@ya.ru>";
static char doc[] =
	"cdates -- show calendar dates from given databases";
static char args_doc[] = "ARG1 ARG2";
static struct argp_option options[5] = {
	{"verbose", 'v', 0, 0, "Produce verbose output", 0},
	{"quiet", 'q', 0, 0, "Do not produce any output", 0},
	{"silent", 's', 0, OPTION_ALIAS, "", 0},
	{"file", 'f', "FILE", 0, "Database path", 0},
	{0},
};
struct arguments {
	int quiet, verbose;
	char *database_path;
};
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state -> input;
	switch (key) {
	case 'q':
	case 's':
		arguments -> quiet = 1;
		break;
	case 'v':
		arguments -> verbose = 1;
		break;
	case 'f':
		arguments -> database_path = arg;
		break;
	case ARGP_KEY_ARG:
		if (state -> arg_num >= 2) argp_usage(state);
		break;
	case ARGP_KEY_END:
		if (state -> arg_num < 2) argp_usage(state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}
static struct argp argp = {options, parse_opt, args_doc, doc, NULL, 0, 0};

int main(int argc, char **argv)
{
	struct arguments arguments;
	arguments.quiet = 0;
	arguments.verbose = 0;
	arguments.database_path = "-";
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	return 0;
}
