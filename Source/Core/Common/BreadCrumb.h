#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define SUB_PATH "Core"

class BreadCrumb
{
	public:
		static void breadcrumb(const char *file, const char *fun, int line) {

			time_t rawtime;
			struct tm * timeinfo;
			time(&rawtime);
			timeinfo = localtime(&rawtime);

			// formatted time string
			char *t = asctime(timeinfo);

			// asctime strings have newline
			BreadCrumb::chomp(t);

			std::cout << KYEL << t << " " << KWHT << path(file) << " " << KCYN << fun << " " << KGRN << line << " " << KNRM << std::endl;
			//printf("%sFROM(%s): %s%s %s%s %s%d %s\n", KYEL, t, KWHT, path(file), KCYN, fun, KGRN, line, KNRM);

		}

	private:
		static void chomp(char *line) {
			char *hold = (char*) memchr(line, '\n', 30);
			if (hold)
				*hold = '\0';
		}
		static char* path(const char *line) {
			return strstr(line, SUB_PATH) + strlen(SUB_PATH) + 1;
		}
		// char* path(const char *line);
};
