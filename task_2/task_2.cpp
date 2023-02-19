#include <iostream>
#include <vector>
#include "sql_query_builder2.h"


int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddColumns(std::vector<std::string>{ "name1", "phone1", "name" });
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");
    query_builder.AddWhere(std::map<std::string, std::string>{ {"id", "50"}, {"name2", "Noname"}});
    std::cout << query_builder.BuildQuery() << std::endl;
    return 0;
}