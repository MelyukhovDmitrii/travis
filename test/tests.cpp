#include <thread>
#include "../myServer.h"
#include "../myClient.h"
#include "gtest/gtest.h"


TEST(lab4_test, connection){
    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
    int n = init(1);
    std::cout.rdbuf(sbuf);
    std::string message = buffer.str();
    ASSERT_TRUE(n == 0);
    ASSERT_TRUE(message.length() > 0);
    message = message.substr(0, 5);
    ASSERT_EQ(message, "hello");
}

TEST(lab4_test, IpRespinseDown){
    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
    int n = init(1);
    std::cout.rdbuf(sbuf);
    std::string message = buffer.str();
    ASSERT_TRUE(n == 0);
    ASSERT_TRUE(message.length() > 0);
    message = message.substr(0, 21);
    ASSERT_EQ(message, "hello\nDOWN 127.0.0.1\n");
}


int main(int argc, char **argv) {
    std::thread t1(initServer);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
