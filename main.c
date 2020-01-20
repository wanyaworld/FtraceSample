#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fd, toggle_fd, method_fd, res;
	char buf[256];

	strcpy(buf, "hi this is test");

	toggle_fd = open("/sys/kernel/debug/tracing/tracing_on", O_RDWR, 0644);
	method_fd = open("/sys/kernel/debug/tracing/current_tracer", O_RDWR, 0644);
	fd = open("sample.txt", O_CREAT | O_WRONLY, S_IRWXU);

	res = write(method_fd, "nop", strlen("nop") + 1);
	res = write(method_fd, "function_graph", strlen("function_graph") + 1);
	res = write(toggle_fd, "1", strlen("1") + 1);

	res = write(fd, buf, strlen(buf) + 1);
	
	res = write(toggle_fd, "0", strlen("0") + 1);
	
	res = close(fd);
	res = close(method_fd);
	res = close(toggle_fd);
	
	return 0;
}
