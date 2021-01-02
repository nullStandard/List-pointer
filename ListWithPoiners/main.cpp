#include "list.h"


int main()
{
	// just debuging
	char arr[] = "Hello!";
	char arr1[] = "Hey!";
	char arr2[] = "Hayhai!";
	char arr3[] = "GeneralKenobi!";

	char** head = nullptr;
	StringListRemoveDuplicates(&head);

	StringListInit(&head);

	StringListAdd(head, arr);
	StringListAdd(head, arr);
	StringListAdd(head, arr);

	StringListAdd(head, arr1);
	StringListAdd(head, arr2);
	StringListAdd(head, arr1);
	StringListAdd(head, arr);
	StringListAdd(head, arr);

	StringListAdd(head, arr3);
	StringListAdd(head, arr3);

	/*auto temp = reinterpret_cast<char**>(head[0]);
	auto temp2 = &temp;*/

	cout << StringListSize(head) << endl;
	PrintList(head);
	StringListRemoveDuplicates(&head);
	//StringListRemove(&head, arr);
	PrintList(head);

	/*StringListRemove(&head, arr);
	PrintList(head);
	StringListRemove(&head, arr1);
	PrintList(head);
	StringListRemove(&head, arr3);
	PrintList(head);
	StringListAdd(head, arr2);
	PrintList(head);*/

	cout << StringListIndexOf(head, arr2) << endl;

	cout << StringListSize(head) << endl;
	PrintList(head);

	StringListDestroy(&head);

	cout << StringListSize(head) << endl;
	PrintList(head);

	/////////////////////////////////////////////////////////////

	/*auto new_node = static_cast<char**>(malloc(2 * sizeof(char)));
	new_node[0] = arr2;
	new_node[1] = arr3;


	cout << *new_node << " " << *(new_node + 1) << endl;

	char** head = static_cast<char**>(malloc(2 * sizeof(char)));
	head[1] = arr;

	head[0] = reinterpret_cast<char*>(new_node);

	char** temp = reinterpret_cast<char**>(head[0]);

	cout << *temp << " " << *(temp + 1);*/


	/////////////////////////////////////////////////////////////

	/*const char* arr3[]{ "Hello", "Hi!" };
	cout << arr3 << " " << *arr3 << endl;

	char** p_arr3 = const_cast<char**>(arr3);
	cout << p_arr3 << p_arr3[0] << " " << *p_arr3 << endl;*/

	/////////////////////////////////////////////////////////////

	system("pause");
}