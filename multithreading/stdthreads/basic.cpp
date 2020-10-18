/*
 * Introduces class std::thread (not CopyConstructible or CopyAssignable), nested class std::thread::id,
 * and namespace std::this_thread
 *
*/

#include <iostream>
#include <string>
#include <thread>

// std is a namespace
// std::thread is a class
// std::thread::id is a nested class
// MainThreadId is an object of class std::thread::id
// get_id is a function in the namespace std::this_thread
std::thread::id MainThreadId = std::this_thread::get_id();

void IsMainThread()
{
  std::thread::id CurrentThreadId = std::this_thread::get_id();
  std::thread::id DefaultThreadId = std::thread::id{};

  if(CurrentThreadId == MainThreadId)
  {
      std::cout << "This is the main thread with id = "<<CurrentThreadId<<" and ";
  }
  else
  {
      std::cout << "This is not the main thread and has id = "<<CurrentThreadId<<" and ";
  }

  /*
   * When a thread is default constructed its id is std::thread::id{}.
   * A thread's id = std::thread::id{} if:
   * 1) it has been created but has no task assigned to it.
   * 2) it has terminated
   * 3) it has been moved
   * 4) it has been detached
   */
  if(CurrentThreadId==DefaultThreadId)
  {
      std::cout<<"is not joinable"<<std::endl;
  }
  else
  {
      std::cout<<"is joinable"<<std::endl;
  }
}

int main()
{
    // Main thread is running here
    // Note: There is no such thing as "main" thread (all threads are first-class citizens :)).
    // Typically the thread which was launched first is called as "main" thread.

    IsMainThread();

    // Create another thread object and assign it work
    std::thread T2{IsMainThread};
    T2.join();

    // T2 has already been joined with the main thread.
    if(!T2.joinable()) // equivalent to checking if(T2.get_id()==std::thread::id{})
    {
        std::cout<<"T2 is not joinable anymore"<<std::endl;
    }

    std::cout<<"End of main"<<std::endl;

    // System thread (T2 here) cannot proceed beyond the lifetime of the main thread.
    // At the end of the scope of the main thread, its destructor is called which checks
    // if there is a system thread that is still running ( = has not yet joined).
    // The main thread terminates the program if it finds a system thread which has not joined yet.

    return 0;
}
