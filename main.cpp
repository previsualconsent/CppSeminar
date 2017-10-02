#include <iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<cmath>

class HighLowPlayer
{
   public:
      HighLowPlayer() : name_("HighLowPlayer") {}
      HighLowPlayer(std::string name)
      {
         name_ = name;
      }
      int pickNumber(int low, int high)
      {
         return (low + high) / 2;
      }
      std::string name() { return name_; }
   private:
      std::string name_;
};

//class BinaryPlayer : public HighLowPlayer
//{
//   public:
//      BinaryPlayer() : HighLowPlayer("BinaryPlayer") {}
//      virtual int pickNumber(int low, int high)
//      {
//         return (low + high) / 2;
//      }
//};

class HighLowGame
{
   public:
      HighLowGame(HighLowPlayer * player) 
         : player_(player) 
      {
         srand(time(NULL));
      }

      void run(int low, int high, bool print = true)
      {
         number_ = (rand() % (high - low)) + low;

         int guess;
         int nguesses = 0;
         do {
            guess = player_->pickNumber(low, high);
            nguesses ++;
            checkNumber(low, high, guess, print);
         }
         while(guess != number_);
         if(print) std::cout << "Got it!" << std::endl;
         nguesses_.push_back(nguesses);
      }

      void checkNumber(int &low, int &high, int guess, bool print = true)
      {
         if(print) std::cout << "(" << low << "-" << high << "): " << guess << std::endl;
         if(guess < number_)
         {
            if(print) std::cout << "TOO LOW" << std::endl;
            low = guess + 1;
         }
         else if(guess > number_)
         {
            if(print) std::cout << "TOO HIGH" << std::endl;
            high = guess - 1;
         }
      }

      void getStats()
      {
         int sum = 0;
         int sum2 = 0;
         for(size_t i = 0; i < nguesses_.size(); i++)
         {
            int n = nguesses_[i];
            sum += n;
            sum2 += n*n;
         }
         float mean = float(sum)/float(nguesses_.size());
         float stddev = std::sqrt( float(sum2)/nguesses_.size() - mean*mean);
         std::cout << "Stats for " << player_->name() << " with " << nguesses_.size() << " tries" << std::endl;
         std::cout << "Mean: " << mean << std::endl;
         std::cout << "Std Dev: " << stddev << std::endl;
      }

   private:
      HighLowPlayer * player_;
      int number_;
      std::vector<int> nguesses_;

};
int main (int argc, char *argv[])
{
   HighLowGame game(new HighLowPlayer());
   int i = 0;
   while(i < 10000)
   {
      game.run(1,100, false);
      i++;
   }
   game.getStats();
}
