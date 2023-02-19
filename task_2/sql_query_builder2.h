#pragma once
#include <set>
#include <map>
#include <algorithm>
#include <vector>


struct SqlSelect {

    std::set<std::string> column_;
    std::map<std::string, std::string> where_;
    std::string from_;

};


class SqlSelectQueryBuilder {

public:

    SqlSelectQueryBuilder() = default;

    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept {
        if (!column.empty()) {
            sqlselect_.column_.insert(column);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        if (!columns.empty()) {
            sqlselect_.column_.insert(columns.begin(), columns.end());
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& from) noexcept {
        if (!from.empty()) {
            sqlselect_.from_ = from;
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value) noexcept {
        if (!column.empty() && !value.empty()) {
            sqlselect_.where_.insert_or_assign(column, value);
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        if (!kv.empty()) {
            sqlselect_.where_.insert(kv.begin(), kv.end());
        }
        return *this;
    }

    std::string BuildQuery() {
        std::string result = "SELECT ";
        if (sqlselect_.column_.empty()) {
            result += "*";
        }
        else {
            std::for_each(sqlselect_.column_.begin(), sqlselect_.column_.end(), [&result](std::string val) { result += val + ", "; });
            result = result.substr(0, result.size() - 2);   //Убираем последнюю запятую
        }
        if (!sqlselect_.from_.empty()) {
            result += " FROM " + sqlselect_.from_ + " WHERE ";
        }
        else return "Error";

        if (!sqlselect_.where_.empty()) {
            for (const auto& [key, value] : sqlselect_.where_) {
                result += key + "=" + value + " AND ";
            }
            result = result.substr(0, result.size() - 5);   //Убираем последнюю AND
        }
        else return "Error";
        return result + ";";
    }

private:

    SqlSelect sqlselect_;
};

