#include "include/App.h"

using namespace std;

int main()
{
    system("clear");
    Parse parser;
    App app(parser);
    app.run();
    return 0;
}