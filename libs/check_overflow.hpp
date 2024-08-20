# include <cstdlib>
# include <string>

using std::string;

inline bool	check_overflow(string s)
{
	unsigned long	u_big;
	unsigned int	u_small;
	long			bigger;
	int				smaller;

	bigger = atoi(s.c_str());
	smaller = atoi(s.c_str());
	if (smaller != bigger)
		return (true);
	u_small = atol(s.c_str());
	u_big = atol(s.c_str());
	bigger = u_big;
	smaller = u_small;
	if (smaller != bigger)
		return (true);
	return (false);
}
