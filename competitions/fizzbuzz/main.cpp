
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>



void fuzbuzz(int num)
{
    for (int i = 0; i <= num; i++)
    {
        if (i % 5 == 0 && i % 3 == 0) std::cout << "FizzBuzz";
        else if (i % 3 == 0) std::cout << "Fizz";
        else if (i % 5 == 0) std::cout << "Buzz";
        else std::cout << i;

        std::cout << std::endl;

    }
}

void twosum()
{
    int target = 0;
    std::vector<int> nums = {0,4,3,0};

    using Result = std::vector<int>;
    using Cache  = std::map<int,int>;

    Cache cache;
    Result result;

    for( int i=0; i < nums.size(); ++i )
    {
        // calculate and find value
        int find_val = target - nums[i];
        Cache::const_iterator it;
        it = cache.find(find_val);
        if ( it != cache.end() )
        {
            result.push_back(i);
            result.push_back(it->second);
        }
        else
        {
            cache[nums[i]] = i;
        }
    }

}




int main(int argc, char *argv[])
{
    //fuzbuzz(15);
    twosum();

}


