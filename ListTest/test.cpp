#include "pch.h"
#include "C:\Users\User\source\repos\ListWithPoiners\ListWithPoiners\list.cpp"

TEST(ListTesting, size) 
{
    char** head = nullptr;
    StringListInit(&head);

    StringListAdd(head, "Hello!");
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Hi!");
    EXPECT_EQ(3, StringListSize(head));
}

TEST(ListTesting, index_of) 
{
    char** head = nullptr;
    StringListInit(&head);
   
    StringListAdd(head, "Hello!");
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Great!");
    EXPECT_EQ(3, StringListIndexOf(head, "Great!"));
}

TEST(ListTesting, RemoveDuplicates)
{
    char** head = nullptr;
    StringListInit(&head);

    StringListAdd(head, "Hello!");
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Great!");
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Hi!");
    StringListRemoveDuplicates(&head);
    EXPECT_EQ(3, StringListSize(head));
}

TEST(ListTesting, two_lists)
{
    char** head1 = nullptr;
    char** head2 = nullptr;

    StringListInit(&head1);
    StringListInit(&head2);

    StringListAdd(head1, "Hello!");
    StringListAdd(head1, "Hi!");
    StringListAdd(head1, "Hi!");
    StringListAdd(head1, "Great!");

    StringListAdd(head2, "Hi!");
    StringListAdd(head2, "Hi!");
    StringListAdd(head2, "Great!");

    StringListRemoveDuplicates(&head1);

    StringListAdd(head2, "Hi!");

    EXPECT_EQ(4, StringListSize(head2));
}

TEST(ListTesting, not_existing_index)
{
    char** head = nullptr;
    StringListInit(&head);
   
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Hi!");
    StringListAdd(head, "Great!");
    EXPECT_EQ(-1, StringListIndexOf(head, "Wow"));
}

int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}