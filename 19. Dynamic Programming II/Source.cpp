#include<iostream>
using namespace std ;
#include<string>
#include<vector>

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

int main() {

	vector<string> words ;
	/*["This", "is", "an", "example", "of", "text", "justification."]
		16
	*/

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

	system("pause");
}