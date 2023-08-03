#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const char* fifoPath = "/tmp/my_fifo";
    mkfifo(fifoPath, 0666);

    int fd = open(fifoPath, O_WRONLY);
    if (fd < 0) {
        perror("open");
    }

    while (true) {
        std::string message;
        std::cout << "type message: ";
        std::getline(std::cin, message);
        int written = write(fd, message.c_str(), message.size());
        std::cout<<"written: "<<written<<std::endl;
    }

    close(fd);
    return 0;
}
