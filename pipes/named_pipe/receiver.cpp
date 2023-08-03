#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char* fifoPath = "/tmp/my_fifo";
    int fd = open(fifoPath, O_RDONLY);

    while (true) {
        char buffer[256];
        int bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            std::cout << "coming message: " << buffer << std::endl;
        }
    }

    close(fd);
    return 0;
}
