#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

struct HTML{
	string type,words="-",contact="-",others,align="";
};

vector<HTML> parts;
int parts_cnt=0,center_al=0;
string title;
char saved='*';

void show_welcom(){
	string logo=R"(  _   _   _____   __  __   _       ____                 
 | | | | |_   _| |  \/  | | |     | __ )    ___   __  __
 | |_| |   | |   | |\/| | | |     |  _ \   / _ \  \ \/ /
 |  _  |   | |   | |  | | | |___  | |_) | | (_) |  >  < 
 |_| |_|   |_|   |_|  |_| |_____| |____/   \___/  /_/\_\
                                                        )"
;
	cout<<" ________________________________________________________"<<endl;
	cout<<logo<<endl;
	cout<<" ________________________________________________________"<<endl;
	cout<<"|            HTMLBox2.0 Develop by Li Xuyang             |"<<endl;
	cout<<"|________________________________________________________|"<<endl;
	cout<<"|文件|n新建HTML|e退出|                                   |"<<endl;
	cout<<"|____|_________|_____|___________________________________|"<<endl;
	cout<<"："; 
}

void show_parts(){
	cout<<" ________________________________________________________"<<endl;
	cout<<" 序号 类型    文字        链接地址               对齐方式"<<endl; 
	for(int i=0;i<parts_cnt;i++){
		cout<<" ";
		cout<<left;
		cout<<setw(6)<<i<<setw(8)<<parts[i].type<<setw(10)<<parts[i].words<<setw(25)<<parts[i].contact<<setw(10)<<parts[i].align<<endl;
	}
	cout<<" ________________________________________________________"<<endl;
}

string creat_html(){
	string html=R"(<!DOCTYPE html>
<html>
<head>
)"
;
	html+="	<title>"+title+"</title>\n";
	html+="</head>\n<body>\n";
	if(center_al){
		html+=R"(<div style="text-align: center;">)";
		html+="\n";
	}
	for(int i=0;i<parts_cnt;i++){
		if(parts[i].type[0]=='h'){
			html+="	<"+parts[i].type+" style=\"text-align:"+parts[i].align+";\""+">"+parts[i].words+"</"+parts[i].type+">\n";
		}else if(parts[i].type=="p"){
			html+="	<"+parts[i].type+" style=\"text-align:"+parts[i].align+";\""+">"+parts[i].words+"</"+parts[i].type+">\n";
		}else if(parts[i].type=="a"){
			html+="	<"+parts[i].type+" style=\"text-align:"+parts[i].align+";\""+" href=" +parts[i].contact+R"( target="_blank">)"+parts[i].words+"</"+parts[i].type+">\n";
		}else if(parts[i].type=="img"){
			html+="	<img src="+parts[i].contact+" alt="+parts[i].words+" style=\"text-align:"+parts[i].align+";\""+">\n";
		}else if(parts[i].type=="br"){
			html+="	<br>\n";
		}else if(parts[i].type=="o"){
			html+="	"+parts[i].words+"\n";
		}
	} 
	if(center_al){
		html+="</div>\n";
	}
	html+="</body>\n</html>";
	return html;
}

void creat_menu(){
    cout<<saved<<" "<<title<<endl;
    cout<<" ________________________________________________________"<<endl;
    cout<<"|文件|s保存|e退出|                                       |"<<endl;
    cout<<"|添加|h标题|p段落|a链接|i图片|br换行|o自定义|____________|"<<endl;
    cout<<"|编辑|d删除|c对齐方式|cl全文居中|________________________|"<<endl;
    cout<<"|____|_____|_________|__________|________________________|"<<endl;
    cout<<"：";
    string order;
    cin>>order;
    saved='*'; 
    if(order=="e"){
        exit(0);
    }else if(order=="s"){
        cout<<" ________________________________________________________"<<endl;
        cout<<creat_html()<<endl;
        ofstream file(title+".html");
        if(file.is_open()){
            file<<creat_html();
            file.close();
            cout<<" 已保存到"<<title<<".html"<<endl;
            saved=' ';
        }else{
            cout<<" 保存失败！"<<endl;
        }
        cout<<" ________________________________________________________"<<endl;
    }else if(order=="h"){
        HTML newh;
        string t;
        cout<<" ________________________________________________________"<<endl;
        cout<<" 标题级别（1~6）：";
        cin>>t;
        cin.ignore();
        newh.type="h"+t;
        cout<<" 标题内容：";
        getline(cin,newh.words);
        parts.push_back(newh);
        parts_cnt++;
        cout<<" 添加成功"<<endl; 
        cout<<" ________________________________________________________"<<endl;
    }else if(order=="p"){
        HTML newh;
        cout<<" ________________________________________________________"<<endl;
        newh.type="p";
        cout<<" 段落内容：";
        cin.ignore();
        getline(cin,newh.words);
        parts.push_back(newh);
        parts_cnt++;
        cout<<" 添加成功"<<endl; 
        cout<<" ________________________________________________________"<<endl;
    }else if(order=="a"){
        HTML newh;
        newh.type="a";
        string t;
        cout<<" ________________________________________________________"<<endl;
        cout<<" 链接文字：";
        cin.ignore();
        getline(cin,newh.words);
        cout<<" 链接地址：";
        getline(cin,t);
        newh.contact ="\""+t+"\"";
        parts.push_back(newh);
        parts_cnt++;
        cout<<" 添加成功"<<endl; 
        cout<<" ________________________________________________________"<<endl;
    }else if(order== "i"){
        HTML newh;
        string t;
        newh.type="img";
        cout<<" ________________________________________________________"<<endl;
        cout<<" 图片地址：";
        cin.ignore();
        getline(cin,t);
        newh.contact ="\""+t+"\"";
        cout<<" 加载失败时的文字：";
        getline(cin,t);
        newh.words ="\""+t+"\"";
        parts.push_back(newh);
        parts_cnt++;
        cout<<" 添加成功"<<endl; 
        cout<<" ________________________________________________________"<<endl;
    }else if(order=="br"){
        HTML newh;
        cout<<" ________________________________________________________"<<endl;
        newh.type="br";
        parts.push_back(newh);
        parts_cnt++;
        cout<<" 添加成功"<<endl;
        cout<<" ________________________________________________________"<<endl; 
    }else if(order=="o"){
    	HTML newh;
		newh.type="o"; 
    	cout<<" ________________________________________________________"<<endl;
    	cout<<" 输入自定义HTML代码：";
    	cin.ignore();
    	getline(cin,newh.words);
    	parts.push_back(newh);
    	parts_cnt++;
    	cout<<" 添加成功"<<endl; 
    	cout<<" ________________________________________________________"<<endl;
	}else if(order=="d"){
    	cout<<" ________________________________________________________"<<endl;
    	cout<<" 要删除的元素编号：";
    	int idx;
    	cin>>idx;
    	if(idx>=0&&idx<parts.size()){
        	parts.erase(parts.begin()+idx);
        	parts_cnt--;
        	cout<<" 删除成功"<<endl;
   		}else{
        	cout<<" 序号无效"<<endl;
    	}
    	cout<<" ________________________________________________________"<<endl;
	}else if(order=="cl"){
		cout<<" ________________________________________________________"<<endl;
		center_al=1;
		cout<<" 设置成功"<<endl;
		cout<<" ________________________________________________________"<<endl;
	}else if(order=="c"){
    	int idx;
    	string align;
    	cout<<" ________________________________________________________"<<endl;
    	cout<<" 要设置的元素编号：";
    	cin>>idx;
    	if(idx>=0 && idx<parts.size()){
        	cout<<" 对齐方式（left/center/right）：";
        	cin>>align;
        	parts[idx].align=align;
        	cout<<" 设置成功"<<endl;
   		}else{
    	    cout<<" 序号无效"<<endl;
    	}
	   	cout<<" ________________________________________________________"<<endl;
	}else{
        cout<<" 无效选项"<<endl;
    }
    show_parts();
    creat_menu();
}

void new_file(){
	parts_cnt=0,center_al=0;
	cout<<" ________________________________________________________"<<endl;
	cout<<" 网页标题：";
	cin.ignore();
	getline(cin,title);
	cout<<" ________________________________________________________"<<endl;
	creat_menu();
}

void root_order(){
	char order;
	cin>>order;
	switch(order){
		case 'n':{
			new_file();
			break;
		}
		case 'e':{
			exit(0);
			break;
		}
		default:
			cout<<" 无效选项"<<endl<<"：";
			root_order();
	}
}

int main(){
	show_welcom();
	root_order(); 
	return 0;
}
