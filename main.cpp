#include "ServerInfo/ServerInfo.hpp"
#include "tester/tester.hpp"

void	test_collection(void)
{
	tester	t;
	int		test_number;

	test_number = 1;
	t.test_CheckIndentation(test_number++);
}

int	main(void)
{
	test_collection();
}
