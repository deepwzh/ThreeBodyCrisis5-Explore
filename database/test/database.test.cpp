#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "game_achieve_accesser.h"

int main(){
    Record * record = new Record("201601060928", 999, 888, 777, 666, "{\"Hello\": \"World\"}", "{\"AAA\": [1,2,3]}", 1, 1);
    // GameAchieveAccesser::uploadGameAchieve(record);
    GameAchieveAccesser::saveGameAchieveLocal(record, "data.json");
    std::vector<Record> records;
    // GameAchieveAccesser::downloadGameAchieve(records, "201601060928");
    // for (const Record & record: records) {
        // std::cout << record.user_id << std::endl;
    // }
    return 0;
}