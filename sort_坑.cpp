
#include<vector>     
#include<algorithm>    
#include  <iostream>
using namespace std;
struct stu {
	int score;
	bool operator<(const stu &s) const {
		//return score <= s.score; //这段代码会出现内存越界，应该算是stl sort一个容易踩到的坑
		return score > s.score;

	}
};

//这段代码会出现内存越界，应该算是stl sort一个容易踩到的坑
//http://www.zhihu.com/question/26901409
int main(int argvc, char **argv) {
	vector<stu> v;
	
	for (unsigned int i = 0; i < 17; i++) {
		stu s;
		s.score = i+1;
		v.push_back(s);
	}
	sort(v.begin(), v.end());
	for (unsigned int i = 0; i < 17; i++) {
		cout << v[i].score <<" ";
	}
	cout << endl;
	return 0;
}
