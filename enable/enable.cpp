#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

static inline void function_set(int enable, const char *file)
{
        char cmd[80];
        snprintf(cmd, sizeof(cmd), "echo %d > /dev/%s", enable, file);
	cout << "Command: " << cmd << endl;
        system(cmd);
}

static inline int function_get(const char *file)
{
	char filename[80];
	char status[1];
	snprintf(filename, sizeof(filename), "/dev/%s", file);
        FILE *fp = fopen(filename, "r+b");
        if (!fp) {
                cerr << "Couldn't open " << file << endl;
		return -1;
	}
	fread(status, 1, 1, fp);
	return status[0] - '0';
}

class Function {
public:
	Function(char *filename) : file(filename) {}
	virtual void set(int enable) {
		function_set(enable, file);
	}
	virtual int get() const {
		return function_get(file);
	}
private:
	char *file;
};

const int delay = 1;
static inline void on_off(Function func[], int n)
{
	func[n].set(1);
	sleep(delay);
	if (func[n].get() != 1)
		cerr << "Turn " << n << " on failed" << endl;
	func[n].set(0);
	sleep(delay);
	if (func[n].get() != 0)
		cerr << "Turn " << n << " off failed" << endl;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " times" << endl;
		exit(1);
	}
	Function func[2] = {
		Function((char*)"ums_enable"),
		Function((char*)"garmin_enable")
	};

	for (int i = 0; i < atoi(argv[1]); ++i) {
		on_off(func, 0);
		on_off(func, 1);
	}
	cout << "Test " << atoi(argv[1]) << " times OK" << endl;
	return 0;
}


