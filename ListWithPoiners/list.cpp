#include "list.h"

#define NEXT_NODE 0
#define STR_VALUE 1

//working properly (probably)
void StringListInit(char*** list)
{
	if (!(*list))
	{
		*list = static_cast<char**>(calloc(2, sizeof(char*)));
		if ((*list))
		{
			(*list)[NEXT_NODE] = nullptr;
			(*list)[STR_VALUE] = nullptr;
		}
	}
}

void StringListDestroy(char*** list)
{
	if (*list)
	{
		//remembering next node before removing
		auto mem_list = *(list)[NEXT_NODE];
		free(*list);
		*list = nullptr;

		//if next node doesn't excist - return
		if (!mem_list)
		{
			return;
		}
		//else moving to next node
		auto temp = reinterpret_cast<char**>(mem_list);

		StringListDestroy(&temp);
	}
}

// working properly (probably)
void StringListAdd(char** list, char* str)
{
	if (list)
	{
		if (!(list[STR_VALUE]))
		{
			list[STR_VALUE] = str;
		}
		else
		{
			//iterate untill next node doesn't excist
			auto iter = list;
			while (iter[NEXT_NODE])
			{
				iter = reinterpret_cast<char**>(iter[NEXT_NODE]);
			}

			//creating dynamically new node and putting it to the end of list
			auto new_node = static_cast<char**>(malloc(2 * sizeof(char*)));
			if (new_node)
			{
				new_node[NEXT_NODE] = nullptr;
				new_node[STR_VALUE] = str;
			}
			//now, next node pointer points on new dynamically created node
			iter[NEXT_NODE] = reinterpret_cast<char*>(new_node);
		}
	}
}

// working properly (probably)
void StringListRemove(char*** list, char* str)
{
	if (*list)
	{
		int index = StringListIndexOf(*list, str);

		//if our str is first in list
		if (index == 0)
		{
			auto to_free = *list;
			//declaring next node as head of list
			*list = reinterpret_cast<char**>((*list)[NEXT_NODE]);
			free(to_free);
			to_free = nullptr;
			return;
		}

		//iteration StringListIndexOf() times to aim index(position) of str
		auto iter = *list;
		for (int i = 0; i < index - 1; ++i)
		{
			iter = reinterpret_cast<char**>(iter[NEXT_NODE]);
		}

		//remembering next node
		auto temp = reinterpret_cast<char**>(iter[NEXT_NODE]);

		// if temp node is last in the list
		if (index == (StringListSize(*list) - 1))
		{
			iter[NEXT_NODE] = nullptr;
			free(temp);
			return;
		}

		//deleting node if it is in the middle of array
		auto temp2 = reinterpret_cast<char**>(temp[NEXT_NODE]);
		iter[NEXT_NODE] = reinterpret_cast<char*>(temp2);
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
			if (!iter[NEXT_NODE])
				break;
			iter = reinterpret_cast<char**>(iter[NEXT_NODE]);
		}
		return length;
	}
	else
	{
		return -1; // list is not initialized
	}
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
			if (!strcmp(iter[STR_VALUE], str))
			{
				return index;
			}
			if (!iter[NEXT_NODE])
			{
				break;
			}
			iter = reinterpret_cast<char**>(iter[NEXT_NODE]);
			++index;
		}
		return -1; // there is no str in the list
	}
}

// almost like a bubble sort
void StringListRemoveDuplicates(char*** list)
{
	if (*list)
	{
		auto iter = *list;
		while (true)
		{
			//checking if we finished comparisons for current node with all others remaining nodes in list
			bool already_iterated = false; 
			if (!iter[NEXT_NODE])
			{
				break;
			}
			auto temp = reinterpret_cast<char**>(iter[NEXT_NODE]);

			while (true)
			{
				if (!strcmp(temp[STR_VALUE], iter[STR_VALUE]))
				{
					auto temp2 = reinterpret_cast<char**>(iter[NEXT_NODE]);
					StringListRemove(list, iter[STR_VALUE]);
					iter = temp2;

					//if we updated head there is no reason to continue iterations...
					already_iterated = true;
					break;
				}
				if (!temp[NEXT_NODE])
				{
					break;
				}
				temp = reinterpret_cast<char**>(temp[NEXT_NODE]);
			}
			if (!already_iterated) //we do not moving to next node untill consider all remaining nodes
			{
				iter = reinterpret_cast<char**>(iter[NEXT_NODE]);
			}
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
			{
				iter_of_first = reinterpret_cast<char**>(iter_of_first[NEXT_NODE]);
			}
			auto iter_of_second = list;
			for (int i = 0; i < index_of_second; ++i)
			{
				iter_of_second = reinterpret_cast<char**>(iter_of_second[NEXT_NODE]);
			}
			//swaping
			char* buf_str = iter_of_second[STR_VALUE];
			iter_of_second[STR_VALUE] = iter_of_first[STR_VALUE];
			iter_of_first[STR_VALUE] = buf_str;
		}
	}
}

// Custom bubble-sorting
// working properly (probably)
void StringListSort(char** list, bool ascending)
{
	if (list)
	{
		// lambdas, that implement ascending/descending
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
				auto iter_next = reinterpret_cast<char**>(iter[NEXT_NODE]);

				if (lambda_ptr(iter[STR_VALUE], iter_next[STR_VALUE]) > 0)
				{
					char* temp = iter[STR_VALUE];
					iter[STR_VALUE] = iter_next[STR_VALUE];
					iter_next[STR_VALUE] = temp;
				}
				iter = reinterpret_cast<char**>(iter[NEXT_NODE]);
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
			cout << iter[STR_VALUE] << " ";
			if (!iter[NEXT_NODE])
				break;

			iter = reinterpret_cast<char**>(iter[NEXT_NODE]);
		}
		cout << endl;
	}
	else
	{
		cerr << "List is already empty\n";
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
