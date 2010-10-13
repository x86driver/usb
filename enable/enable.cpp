#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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
	cout << file << " status: " << status << endl;
	return 0;
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

int main()
{
	Function func[2] = {
		Function((char*)"ums_enable"),
		Function((char*)"garmin_enable")
	};

	func[0].get();
	func[1].get();
	return 0;
}


