#ifndef COMMON_H
#define COMMON_H


#define $(variable, specifier)                					\
	do 									\
	{									\
		printf( "%s: %" #specifier "\n", #variable, variable);		\
		fflush( stdout);						\
	}									\
	while (0)


#endif // COMMON_H
