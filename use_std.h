# ifndef HEAD_use_std_h
# define HEAD_use_std_h

#include <string>
#include <vector>


bool space(char c);
bool not_space(char c);

bool is_palindrome(const std::string& s);

bool not_url_char(char c);
std::string::const_iterator url_end(std::string::const_iterator b, std::string::const_iterator e);
std::string::const_iterator url_beg(std::string::const_iterator b, std::string::const_iterator e);
std::vector<std::string> find_urls(const std::string& s);

std::vector<std::string> split(const std::string& str);
std::string::size_type width(const std::vector<std::string>& v);
std::vector<std::string> frame(const std::vector<std::string>& v);

std::vector<std::string> vcat(const std::vector<std::string>& top, const std::vector<std::string>& bottom);
std::vector<std::string> hcat(const std::vector<std::string>& left, const std::vector<std::string>& right);


#endif // !HEAD_use_std_h