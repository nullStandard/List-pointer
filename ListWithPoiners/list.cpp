#include "list.h"

//working properly (probably)
void StringListInit(char*** list)
{
	if (!(*list))
	{
		*list = static_cast<char**>(calloc(2, sizeof(char*)));
		(*list)[0] = nullptr;
		(*list)[1] = nullptr;
	}
}

//working properly (probably)
void StringListDestroy(char*** list)
{
	if (*list)
	{
		auto mem_list = *(list)[0];
		auto temp = reinterpret_cast<char**>(*(list)[0]);
		free(*list);
		*list = nullptr;

		if (!mem_list)
		{
			return;
		}

		StringListDestroy(&temp);
	}
}

// working properly (probably)
void StringListAdd(char** list, char* str)
{
	if (list)
	{
		if (!(list[1]))
		{
			list[1] = str;
		}
		else
		{
			auto iter = list;
			while (iter[0])
			{
				iter = reinterpret_cast<char**>(iter[0]);
			}

			auto new_node = static_cast<char**>(malloc(2 * sizeof(char*)));
			new_node[0] = nullptr;
			new_node[1] = str;

			iter[0] = reinterpret_cast<char*>(new_node);
		}
	}
}

// working properly (probably)
void StringListRemove(char*** list, char* str)
{
	if (*list)
	{
		int index = StringListIndexOf(*list, str);
		if (index == 0)
		{
			auto to_free = *list;
			*list = reinterpret_cast<char**>((*list)[0]);
			free(to_free);
			to_free = nullptr;
			return;
		}

		auto iter = *list;
		for (int i = 0; i < index - 1; ++i)
		{
			iter = reinterpret_cast<char**>(iter[0]);
		}

		auto temp = reinterpret_cast<char**>(iter[0]);

		// if node is last in the list
		if (index == (StringListSize(*list) - 1))
		{
			iter[0] = nullptr;
			free(temp);
			return;
		}

		auto temp2 = reinterpret_cast<char**>(temp[0]);
		iter[0] = reinterpret_cast<char*>(temp2);
		free(temp);
	}
}

// working properly (probably)
int StringListSize(char** list)
{

	if (list) // only if list is initialized
	{
		int length = 0;

		auto iter = list;
		while (true)
		{
			++length;
			if (!iter[0])
				break;
			iter = reinterpret_cast<char**>(iter[0]);
		}
		return length;
	}
	else
		return -1;
}

// working properly (probably)
int StringListIndexOf(char** list, char* str)
{
	if (list)
	{
		int index = 0;

		auto iter = list;
		while (true)
		{
			if (!strcmp(iter[1], str))
			{
				return index;
			}
			if (!iter[0])
				break;
			iter = reinterpret_cast<char**>(iter[0]);
			++index;
		}
		return -1;
	}
}

// working properly (probably)
void StringListRemoveDuplicates(char*** list)
{
	if (*list)
	{
		auto iter = *list;
		while (true)
		{
			bool already_iterated = false;
			if (!iter[0])
				break;

			auto temp = reinterpret_cast<char**>(iter[0]);

			while (true)
			{
				if (!strcmp(temp[1], iter[1]))
				{
					auto temp2 = reinterpret_cast<char**>(iter[0]);
					StringListRemove(list, iter[1]);
					iter = temp2;
					already_iterated = true;
					break;
				}
				if (!temp[0])
					break;
				temp = reinterpret_cast<char**>(temp[0]);
			}
			if (!already_iterated)
				iter = reinterpret_cast<char**>(iter[0]);
		}
	}
}

// working properly (probably)
void StringListReplaceInStrings(char** list, char* before, char* after)
{
	if (list)
	{
		int index_of_first = StringListIndexOf(list, before);
		int index_of_second = StringListIndexOf(list, after);

		if ((index_of_first != -1) && (index_of_second != -1))
		{
			auto iter_of_first = list;
			for (int i = 0; i < index_of_first; ++i)
				iter_of_first = reinterpret_cast<char**>(iter_of_first[0]);

			auto iter_of_second = list;
			for (int i = 0; i < index_of_second; ++i)
				iter_of_second = reinterpret_cast<char**>(iter_of_second[0]);

			char* buf_str = iter_of_second[1];
			iter_of_second[1] = iter_of_first[1];
			iter_of_first[1] = buf_str;
		}
	}
}

// Custom bubble-sorting
// working properly (probably)
void StringListSort(char** list, bool ascending)
{
	if (list)
	{
		// lambdas, that implement ascending/descending predicats
		/////////////////////////////////////////////////////////
		auto lambda_ascending
		{
			[](char* a, char* b)->int
				{
					return strcmp(a, b);
				}
		};

		auto lambda_descending
		{
			[](char* a, char* b)->int
				{
					return -strcmp(a, b);
				}
		};
		/////////////////////////////////////////////////////////

		int (*lambda_ptr)(char* a, char* b);

		// ternary operator to chosing what exactly we want: ascending or descending sorting
		(ascending) ?
			lambda_ptr = static_cast<int(*)(char* a, char* b)>(lambda_ascending)	// true
			:
			lambda_ptr = static_cast<int(*)(char* a, char* b)>(lambda_descending);	// false

		int size = StringListSize(list);
		for (int i = 0; i < size - 1; ++i)
		{
			auto iter = list;
			for (int j = 0; j < size - i - 1; ++j)
			{
				auto iter_next = reinterpret_cast<char**>(iter[0]);

				if (lambda_ptr(iter[1], iter_next[1]) > 0)
				{
					char* temp = iter[1];
					iter[1] = iter_next[1];
					iter_next[1] = temp;
				}
				iter = reinterpret_cast<char**>(iter[0]);
			}
		}
	}
}

//working properly (probably)
void PrintList(char** list)
{
	if (list)
	{
		auto iter = list;
		while (true)
		{
			cout << iter[1] << " ";
			if (!iter[0])
				break;

			iter = reinterpret_cast<char**>(iter[0]);
		}
		cout << endl;
	}
	else
	{
		cout << "List is already empty" << endl;
	}
}

void Interaction::showCommands()
{
	printf("%s\n", "Command signatures: ");
	printf("%s\n", "i \tinit the list;");
	printf("%s\n", "a \tadd a new string to the list;");
	printf("%s\n", "d \tdestroy the list;");
	printf("%s\n", "ro \tremove all occurrences of string in the list");
	printf("%s\n", "s \tget the number of items in the list");
	printf("%s\n", "ind \tget the index position of the first occurrence of string in the list");
	printf("%s\n", "rd \tremove duplicate entries from the list");
	printf("%s\n", "rp \treplace every occurrence of the before, in each of the string lists's strings, with after");
	printf("%s\n", "srt \tsort the list of strings in chosen order (ascending by default)");
	printf("%s\n", "p \tprint the list");
	printf("%s\n", "q \tquit");
	printf("%s\n\n", "c \tshow command signatures again");
	printf("%s\n\n", "First of all, you have to initialize the list");
}

void Interaction::input()
{
	while (true)
	{
		char command[4];
		printf("%s", "Enter command code: ");
		scanf("%s", command);

		if (!strcmp(command, "i"))
		{
			StringListInit(&head);
		}
		else if (!strcmp(command, "a"))
		{
			char* arr = (char*)malloc(20 * sizeof(char));
			scanf("%s", arr);
			StringListAdd(head, arr);
			PrintList(head);
		}
		else if (!strcmp(command, "d"))
		{
			StringListDestroy(&head);
		}
		else if (!strcmp(command, "ro"))
		{
			char* arr = (char*)malloc(20 * sizeof(char));
			scanf("%s", arr);
			StringListRemove(&head, arr);
			PrintList(head);
		}
		else if (!strcmp(command, "s"))
		{
			std::cout << "List size: " << StringListSize(head) << std::endl;
		}
		else if (!strcmp(command, "ind"))
		{
			char* arr = (char*)malloc(20 * sizeof(char));
			scanf("%s", arr);
			std::cout << "Index of  \"" << arr << "\" is " << StringListIndexOf(head, arr) << std::endl;
		}
		else if (!strcmp(command, "rd"))
		{
			StringListRemoveDuplicates(&head);
			PrintList(head);
		}
		else if (!strcmp(command, "rp"))
		{
			char* before = (char*)malloc(20 * sizeof(char));
			scanf("%s", before);
			char* after = (char*)malloc(20 * sizeof(char));
			scanf("%s", after);
			StringListReplaceInStrings(head, before, after);
			PrintList(head);
		}
		else if (!strcmp(command, "srt"))
		{
			char choose;
			printf("%s", "acsending by default, choose descending? (y/n): ");
			std::cin >> choose;
			(choose == 'y') ? StringListSort(head, false) : StringListSort(head);
			PrintList(head);
		}
		else if (!strcmp(command, "p"))
		{
			PrintList(head);
		}
		else if (!strcmp(command, "q"))
		{
			return;
		}
		else if (!strcmp(command, "q"))
		{
			return;
		}
		else if (!strcmp(command, "c"))
		{
			printf("\n");
			showCommands();
		}
		else
		{
			printf("%s\n", "Command doesn't exist, try again.");
		}
	}
}
