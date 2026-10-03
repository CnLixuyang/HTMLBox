#include<Fl/Fl.H>
#include<Fl/Fl_Window.H>
#include<Fl/Fl_Box.H>
#include<Fl/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/fl_ask.H>
#include <cstdlib>
#include"HTMLBoxCore1.h"

Fl_Window *creatmenu;
Fl_Input *creatinput;
Fl_Input *titlewordinput;
Fl_Input *titletypeinput;
Fl_Input *paragraphwordinput;
Fl_Input *imagesrcinput;
Fl_Input *imagealtinput;
Fl_Input *linkurlinput;
Fl_Input *linktextinput;
Fl_Input *custominput;
Fl_Multiline_Output *htmlout;

void addtitle_cb(Fl_Widget *w, void *data){
	core_addTitle(atoi(titletypeinput->value()),titlewordinput->value());
	htmlout->value((core_getHTML()).c_str());
	creatmenu->copy_label(("HTMLBox Pro 2 "+core_isSaved()+core_getTitle()).c_str());
	htmlout->redraw();
	creatmenu->redraw();
	Fl::flush();
	Fl_Window* win = (Fl_Window*)data;
	win->hide();
}

void addtitleui_cb(Fl_Widget *w, void *data){
	Fl_Window *addtitlewindow=new Fl_Window(400,200,"添加标题");
	titlewordinput=new Fl_Input(100,50,250,30,"   内容：");
	titletypeinput=new Fl_Input(100,90,250,30,"级别1-6：");
	Fl_Button *ok=new Fl_Button(150,150,100,30,"添加");
	ok->callback(addtitle_cb,addtitlewindow);
	addtitlewindow->end();
	addtitlewindow->show();
}

void savefile_cb(Fl_Widget *w, void *data){
	if(core_saveToFile()){
		fl_message("已保存");
	}else{
		fl_message("保存时出错");
	}
	creatmenu->copy_label(("HTMLBox Pro 2 "+core_isSaved()+core_getTitle()).c_str());
	creatmenu->redraw();
	Fl::flush();
}

void addparagraph_cb(Fl_Widget *w, void *data){
	core_addParagraph(paragraphwordinput->value());
	htmlout->value((core_getHTML()).c_str());
	creatmenu->copy_label(("HTMLBox Pro 2 "+core_isSaved()+core_getTitle()).c_str());
	htmlout->redraw();
	creatmenu->redraw();
	Fl::flush();
	Fl_Window* win = (Fl_Window*)data;
	win->hide();
}

void addparagraphui_cb(Fl_Widget *w, void *data){
	Fl_Window *addparagraphwindow=new Fl_Window(400,200,"添加段落");
	paragraphwordinput=new Fl_Input(100,50,250,30,"    内容：");
	Fl_Button *ok=new Fl_Button(150,150,100,30,"添加");
	ok->callback(addparagraph_cb,addparagraphwindow);
	addparagraphwindow->end();
	addparagraphwindow->show();
}

void addimage_cb(Fl_Widget *w, void *data){
	core_addImage(imagesrcinput->value(),imagealtinput->value());
	htmlout->value((core_getHTML()).c_str());
	creatmenu->copy_label(("HTMLBox Pro 2 "+core_isSaved()+core_getTitle()).c_str());
	htmlout->redraw();
	creatmenu->redraw();
	Fl::flush();
	Fl_Window* win = (Fl_Window*)data;
	win->hide();
}

void addimageui_cb(Fl_Widget *w, void *data){
	Fl_Window *addimagewindow=new Fl_Window(400,200,"添加图片");
	imagesrcinput=new Fl_Input(100,50,250,30,"    地址：");
	imagealtinput=new Fl_Input(100,90,250,30,"失败文字：");
	Fl_Button *ok=new Fl_Button(150,150,100,30,"添加");
	ok->callback(addimage_cb,addimagewindow);
	addimagewindow->end();
	addimagewindow->show();
}

void addlink_cb(Fl_Widget *w, void *data){
	core_addLink(linktextinput->value(),linkurlinput->value());
	htmlout->value((core_getHTML()).c_str());
	creatmenu->copy_label(("HTMLBox Pro 2 "+core_isSaved()+core_getTitle()).c_str());	
	htmlout->redraw();
	creatmenu->redraw();
	Fl::flush();
	Fl_Window* win = (Fl_Window*)data;
	win->hide();
}

void addlinkui_cb(Fl_Widget *w, void *data){
	Fl_Window *addlinkwindow=new Fl_Window(400,200,"添加链接");
	linkurlinput=new Fl_Input(100,50,250,30,"    地址：");
	linktextinput=new Fl_Input(100,90,250,30,"链接文字：");
	Fl_Button *ok=new Fl_Button(150,150,100,30,"添加");
	ok->callback(addlink_cb,addlinkwindow);
	addlinkwindow->end();
	addlinkwindow->show();
}

void addlinebreak_cb(Fl_Widget *w, void *data){
	core_addLineBreak();
	htmlout->value((core_getHTML()).c_str());
	creatmenu->copy_label(("HTMLBox Pro 2 "+core_isSaved()+core_getTitle()).c_str());
	htmlout->redraw();
	creatmenu->redraw();
	Fl::flush();
}

void addcustom_cb(Fl_Widget *w, void *data){
	core_addCustom(custominput->value());
	htmlout->value((core_getHTML()).c_str());
	creatmenu->copy_label(("HTMLBox Pro 2 "+core_isSaved()+core_getTitle()).c_str());	
	htmlout->redraw();
	creatmenu->redraw();
	Fl::flush();
	Fl_Window* win = (Fl_Window*)data;
	win->hide();
}

void addcustomui_cb(Fl_Widget *w, void *data){
	Fl_Window *addcustomwindow=new Fl_Window(400,200,"添加自定义");
	custominput=new Fl_Input(100,50,250,90,"    代码：");
	Fl_Button *ok=new Fl_Button(150,150,100,30,"添加");
	ok->callback(addcustom_cb,addcustomwindow);
	addcustomwindow->end();
	addcustomwindow->show();
}

void centerall_cb(Fl_Widget *w, void *data){
	core_setCenterAll(!core_isCenterAll());
	htmlout->value((core_getHTML()).c_str());
	creatmenu->copy_label(("HTMLBox Pro 2 "+core_isSaved()+core_getTitle()).c_str());
	htmlout->redraw();
	creatmenu->redraw();
	Fl::flush();
}

void showcreatmenu(){
	creatmenu=new Fl_Window(800,500,("HTMLBox Pro 2 "+core_isSaved()+core_getTitle()).c_str());
	Fl_Box *hellobox=new Fl_Box(30,30,610,30,"HTMLBox Pro 2");
	hellobox->box(FL_UP_BOX);
	hellobox->labelsize(20);
	htmlout= new Fl_Multiline_Output(30,90,610,380);
	htmlout->value((core_getHTML()).c_str());
	Fl_Button *savefile=new Fl_Button(670,30,100,30,"保存");
	savefile->callback(savefile_cb);
	Fl_Button *addtitle=new Fl_Button(670,90,100,30,"添加标题");
	addtitle->callback(addtitleui_cb);
	Fl_Button *addparagraph=new Fl_Button(670,130,100,30,"添加段落");
	addparagraph->callback(addparagraphui_cb);
	Fl_Button *addimage=new Fl_Button(670,170,100,30,"添加图片");
	addimage->callback(addimageui_cb);
	Fl_Button *addlink=new Fl_Button(670,210,100,30,"添加链接");
	addlink->callback(addlinkui_cb);
	Fl_Button *addlinebreak=new Fl_Button(670,250,100,30,"添加换行");
	addlinebreak->callback(addlinebreak_cb);
	Fl_Button *addcustom=new Fl_Button(670,290,100,30,"添加自定义");
	addcustom->callback(addcustomui_cb);
	Fl_Button *centerall=new Fl_Button(670,330,100,30,"全局居中");
	centerall->callback(centerall_cb);
	creatmenu->end();
	creatmenu->show();
}

void exitbutton_cb(Fl_Widget *w, void *data){
	exit(0);
}

void creatnew_cb(Fl_Widget *w, void *data){
	core_newProject(creatinput->value());
	Fl_Window* win = (Fl_Window*)data;
	win->hide();
	showcreatmenu();
}

void creatbutton_cb(Fl_Widget *w, void *data){
	Fl_Window *creatnewwindow=new Fl_Window(400,200,"新建HTML");
	creatinput=new Fl_Input(50,50,300,30,"标题：");
	Fl_Button *ok=new Fl_Button(150,150,100,30,"新建");
	ok->callback(creatnew_cb,creatnewwindow);
	creatnewwindow->end();
	creatnewwindow->show();
}

int main(){
	Fl_Window *rootwindow=new Fl_Window(500,300,"HTMLBox Pro 2");
	Fl_Box *hellobox=new Fl_Box(20,20,460,200,"HTMLBox Pro 2");
	hellobox->box(FL_UP_BOX);
	hellobox->labelsize(30);
	
	Fl_Button *creatbutton=new Fl_Button(20,240,100,30,"创建HTML");
	creatbutton->callback(creatbutton_cb);
	Fl_Button *exitbutton=new Fl_Button(140,240,100,30,"退出");
	exitbutton->callback(exitbutton_cb);
	
	rootwindow->end();
	rootwindow->show();
	return Fl::run();
}
