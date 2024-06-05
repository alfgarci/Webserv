#include "ServerInfo/ServerInfo.hpp"
#include "tester/tester.hpp"

void	test_collection(void)
{
	tester	t;
	int		test_number;

	test_number = 1;
	t.test_check_indentation(test_number);
	t.test_check_indentation_level(test_number);
}

int	main(void)
{
	test_collection();
}
