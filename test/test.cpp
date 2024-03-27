#include <iostream>
#include <vector>
#include <string>
#include <memory>

//test
#include "fmt_test.hpp"
#include "log.hpp"

int main(int argc, char** argv) 
{
    // 1.fmt test
    std::shared_ptr<CFmtTest> Fmt = std::make_shared<CFmtTest>();;
    Fmt->FmtTest();

    CALMCAR_INFO_S("test log");

    return 0;
}