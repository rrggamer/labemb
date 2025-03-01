#include <Arduino.h>
#include <kociemba.h>

// char test_cube[] = "RDLUULLUDRDDDRLDRBULBUFBRULDFBFDFUFLFBFRLRRLFFRUBBBUDB";
// char test_cube[] = "RUUFUDRDDBRLURDUFFULLRFBRBBDLLFDDRRLBRBLLBUUFFLDBBFDUF";
char test_cube[] = "LRRBURRBBRFURRFDRLDLUUFUFFBDDRDDDLUUUDFFLBBLLFBFUBLBLD";
// char test_cube[] = "UUUUUUUUU RRRRRRRRR FFFFFFFFF DDDDDDDDD LLLLLLLLL BBBBBBBBB";

// char test_cube[] = "RDLUULLUD RDDDRLDRB ULBUFBRUL DFBFDFUFL FRUBBBUDB FBFRLRRLF";

elapsedMillis em;

DMAMEM char buf479[479*1024];   // 479K in DMAMEM
char  buf248[248 * 1024];       // 248K on in DTCM 

void setup() {
    while (!Serial);
    em = 0;
    kociemba::set_memory(buf479, buf248);
    Serial.printf("RAM buffer created in %d ms.\n", (int)em);
}

void loop() {
    em = 0;
    const char* res = kociemba::solve(test_cube);
    if (res == nullptr)
        Serial.println("No solution found :(");
    else
        Serial.printf("Solution [%s] found in %d ms.\n", res, (int)em);

    delay(5000);  // Prevent spamming
}
