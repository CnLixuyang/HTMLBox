#ifndef HTMLBOX_CORE1_H
#define HTMLBOX_CORE1_H

#include <string>
#include <vector>
#include <fstream>

// ========== 数据结构 ==========
struct HTML{
	std::string type, words="-", contact="-", others="", align="";
};

struct STEP{
	std::vector<HTML> parts;
	bool center_all;
};

// ========== 全局变量（static 限定本文件，避免链接冲突） ==========
static std::vector<HTML> core_parts;
static std::vector<STEP> core_steps;
static bool core_center_all=false;
static std::string core_title;
static std::string core_saved="*";
static bool core_saveToFile(const std::string& filename);

// ========== 内部工具 ==========
static void core_saveStep(){
	STEP s;
	s.parts=core_parts;
	s.center_all=core_center_all;
	core_steps.push_back(s);
}

// ========== 项目操作 ==========
static void core_newProject(const std::string& projectTitle){
	core_parts.clear();
	core_steps.clear();
	core_parts.shrink_to_fit();
	core_steps.shrink_to_fit();
	core_center_all=false;
	core_title=projectTitle;
	core_saved="*";
}

static std::string core_getHTML(){
	std::string html=R"(<!DOCTYPE html>
<html>
<head>
)";
	html+="	<title>"+core_title+"</title>\n";
	html+="</head>\n<body>\n";
	if(core_center_all){
		html+=R"(<div style="text-align: center;">)";
		html+="\n";
	}
	for(size_t i=0;i<core_parts.size();i++){
		if(core_parts[i].type[0]=='h'){
			html+="	<"+core_parts[i].type+" style=\"text-align:"+core_parts[i].align+";\">"+core_parts[i].words+"</"+core_parts[i].type+">\n";
		}else if(core_parts[i].type=="p"){
			html+="	<p style=\"text-align:"+core_parts[i].align+";\">"+core_parts[i].words+"</p>\n";
		}else if(core_parts[i].type=="a"){
			html+="	<a style=\"text-align:"+core_parts[i].align+";\" href="+core_parts[i].contact+" target=\"_blank\">"+core_parts[i].words+"</a>\n";
		}else if(core_parts[i].type=="img"){
			html+="	<img src="+core_parts[i].contact+" alt="+core_parts[i].words+" style=\"text-align:"+core_parts[i].align+";\">\n";
		}else if(core_parts[i].type=="br"){
			html+="	<br>\n";
		}else if(core_parts[i].type=="o"){
			html+="	"+core_parts[i].words+"\n";
		}
	}
	if(core_center_all){
		html+="</div>\n";
	}
	html+="</body>\n</html>";
	return html;
}

static bool core_saveToFile(){
	return core_saveToFile(core_title+".html");
}

static bool core_saveToFile(const std::string& filename){
	std::ofstream file(filename);
	if(!file.is_open()) return false;
	file<<core_getHTML();
	file.close();
	core_saved=" ";
	return true;
}

// ========== 元素操作 ==========
static void core_addTitle(int level, const std::string& content){
	if(level<1||level>6) level=1;
	core_saveStep();
	HTML h;
	h.type="h"+std::to_string(level);
	h.words=content;
	core_parts.push_back(h);
	core_saved="*";
}

static void core_addParagraph(const std::string& content){
	core_saveStep();
	HTML h;
	h.type="p";
	h.words=content;
	core_parts.push_back(h);
	core_saved="*";
}

static void core_addLink(const std::string& text, const std::string& url){
	core_saveStep();
	HTML h;
	h.type="a";
	h.words=text;
	h.contact="\""+url+"\"";
	core_parts.push_back(h);
	core_saved="*";
}

static void core_addImage(const std::string& src, const std::string& alt="图片"){
	core_saveStep();
	HTML h;
	h.type="img";
	h.contact="\""+src+"\"";
	h.words="\""+alt+"\"";
	core_parts.push_back(h);
	core_saved="*";
}

static void core_addLineBreak(){
	core_saveStep();
	HTML h;
	h.type="br";
	core_parts.push_back(h);
	core_saved="*";
}

static void core_addCustom(const std::string& code){
	core_saveStep();
	HTML h;
	h.type="o";
	h.words=code;
	core_parts.push_back(h);
	core_saved="*";
}

static bool core_deleteElement(int index){
	if(index<0||index>=(int)core_parts.size()) return false;
	core_saveStep();
	core_parts.erase(core_parts.begin()+index);
	core_saved="*";
	return true;
}

// ========== 编辑操作 ==========
static bool core_setAlign(int index, const std::string& align){
	if(index<0||index>=(int)core_parts.size()) return false;
	core_saveStep();
	core_parts[index].align=align;
	core_saved="*";
	return true;
}

static void core_setCenterAll(bool on){
	core_saveStep();
	core_center_all=on;
	core_saved="*";
}

static bool core_undo(){
	if(core_steps.empty()) return false;
	STEP last=core_steps.back();
	core_steps.pop_back();
	core_parts=last.parts;
	core_center_all=last.center_all;
	core_saved="*";
	return true;
}

// ========== 查询 ==========
static int core_getElementCount(){
	return (int)core_parts.size();
}

static HTML core_getElement(int index){
	if(index<0||index>=(int)core_parts.size()) return HTML();
	return core_parts[index];
}

static std::string core_getTitle(){
	return core_title;
}

static bool core_isCenterAll(){
	return core_center_all;
}

static std::string core_isSaved(){
	return core_saved;
}

#endif
