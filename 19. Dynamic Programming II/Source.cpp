#include<iostream>
using namespace std ;
#include<string>
#include<vector>
#include<unordered_map>

// 1. Text Justifications
long baddness(vector<string>& words ,int i ,int j,int maxWidth){
        int width = 0 ;

        for (;i<=j ; i++){
            width += (words[i].size() +1);
        }
        width-- ;
		if(maxWidth >= width)
			return pow(maxWidth-width , 3 );
		else
			return INT_MAX;
    }
    
int calc_for_i(vector<string>& words ,int i,int maxWidth , vector<int> &wordsWeight,vector<int>& stops){
	if(i==words.size())
		return 0;

	if(wordsWeight[i]!=0) // as i initialized all as 0s
		return wordsWeight[i] ;

	        int min =INT_MAX ;
            for(int j=i+1;j<=words.size();j++){
				int bad = baddness(words,i,j-1,maxWidth);
				int calculation = calc_for_i(words,j,maxWidth,wordsWeight,stops);
				if(bad!=INT_MAX &&  calculation + bad < min){
                    min = calculation + bad;
                    stops[i]= j-1 ;   
                }
            }
            wordsWeight[i] = min ;

}

vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> solution;
        vector<int> wordsWeight(words.size(),0); 
        vector<int> stops(words.size(),-1);

		// we need to call that function for i = 0 as our start;
		calc_for_i(words,0,maxWidth,wordsWeight,stops);

		int wordsPut = 0 ;
		int i=0;
		while(i<words.size()){
				if(stops[i]==-1) // mean last sentence
				{
					stops[i]=words.size()-1;
				}
                string x ;
				int spaces=0;
				int count = 0;

				for (int j = i; j <= stops[i]; j++)
				{
					spaces += words[j].size();
					count ++ ;
				}
				spaces = maxWidth - spaces ;
				
				for (int i = wordsPut; i < count+wordsPut; i++)
				{
					if(i!=count+wordsPut-1)
						x+= words[i] + " " ;
					else
						x+= words[i] ;

				}
				solution.push_back(x) ;
				wordsPut+=count ;
				i=stops[i]+1;
			
            }
            return solution; 

}

//////////////////////////////////////////////////////////////////////////////////////////////////

// 2. BlackJack problem
	/*
	in blackjack the goal is to beat the dealer the player wins if his hand as a higher value than the dealers without going bust
	the player also wins if the dealer busts and the player doesn't.
	busting is when the total value of the hand goes over 21
	and when players bust they automatically lose regardless of whether the dealer busts or not
	
	A(10,K,Q,J) -> TREATED 21 SO BLACKJACK so player auto wins unless dealer also got a blackjack!
	
	in this algorithm we have no splitting
	*/

// so our algorithm is to make most money out of blackjack (win-> +1$ , lose-> -1$ , draw-> 0$ ) 
	// so you could lose 1 game in order to win more games (upcoming!!) as we know the deck WOOW.


// SO DISTRIBUTION 
	// THATS VERY IMPORTANT 
			//( IF DECK CO C1 C2 C3 ) 
			// you : C0  C2
			// dealer : C1(SEEN) C3(UNSEEN FOR DEALER)
			// BUT SEEN FOR YOU FORTUNATELY !!!!!!!!!!!!!!!

// later will do BJ IMPLEMENTATION !	


int main() {

	vector<string> words ;
	
	//["This", "is", "an", "example", "of", "text", "justification."]
	//	16
	//

	string input[18] = {"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
	
	for (int i = 0; i < 18; i++)
	{
		words.push_back(input[i]);
	}
	vector<string> sol = fullJustify(words,16);
	for (int i = 0; i < sol.size(); i++)
	{
		cout<<sol[i] << endl;
	}
	


	//unordered_map<string,int> cardsValue;
	//for (int i = 2; i <= 10; i++)
	//{
	//	cardsValue[to_string(i)] = i ;
	//}
	//cardsValue["K"] = 10;
	//cardsValue["Q"] = 10;
	//cardsValue["J"] = 10;

	//cardsValue["A"] = 1; // we will initialize it =1 but will check above if its A so we set it 1 or 11


	system("pause");
}