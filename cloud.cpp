#include "util.hpp"
#include"data.hpp"
#include "hot.hpp"
#include"server.hpp"
#include <thread>
void FileUtilTest()
{
  //cloud::FileUtil("./testdir/adir").CreateDirectory();
  //cloud::FileUtil("./testdir/a.txt").Write("hello lc\n");
 // std::string body;
  //cloud::FileUtil("./testdir/a.txt").Read(&body);
  //std::cout<<cloud::FileUtil("./testdir/a.txt").Size()<<std::endl;
  //std::cout<<cloud::FileUtil("./testdir/a.txt").Mtime()<<std::endl;
  //std::cout<<cloud::FileUtil("./testdir/a.txt").Atime()<<std::endl;
  std::vector<std::string> arry;
  cloud::FileUtil("./testdir/").ScanDirectory(&arry);
  for(auto &e :arry)
  {
    std::cout<<e<<std::endl;
  }
}
void JsonTest()
{
  Json::Value val;
  val["姓名"]="小黑";
  val["年龄"]=19;
  val["性别"]="男";
  val["成绩"].append(80);
  val["成绩"].append(85);
  val["成绩"].append(90);

  std::string body;
  cloud::JsonUtil::Serialize(val,&body);
  std::cout<<body<<std::endl;

  Json::Value root;
  cloud::JsonUtil::UnSerialize(body,&root);
  std::cout<<root["姓名"].asString()<<std::endl;
  std::cout<<root["年龄"].asInt()<<std::endl;
  std::cout<<root["性别"].asString()<<std::endl;
  std::cout<<root["成绩"][0].asString()<<std::endl;
  std::cout<<root["成绩"][1].asString()<<std::endl;
  std::cout<<root["成绩"][2].asString()<<std::endl;
}
void CompressTest()
{
  cloud::FileUtil("./hello.txt").Compress("hello.zip");
  cloud::FileUtil("./hello.zip").UnCompress("bit.txt");
}
void DataTest()
{
  cloud::DataManager data;
  std::vector<cloud::FileInfo> arry;
  data.SelectAll(&arry);
  for(auto &e : arry)
  {
    std::cout<<e.filename<<std::endl;
    std::cout<<e.url_path<<std::endl;
    std::cout<<e.real_path<<std::endl;
    std::cout<<e.file_size<<std::endl;
    std::cout<<e.back_time<<std::endl;
    std::cout<<e.pack_flag<<std::endl;
    std::cout<<e.pack_path<<std::endl;
  }
  /*
  cloud::DataManager data;
  data.Insert("./backup_dir/hello.txt");
  data.UpdateStatus("./backup_dir/hello.txt",true);
  std::vector<cloud::FileInfo> arry;
  data.SelectAll(&arry);
  for(auto &e : arry)
  {
    std::cout<<e.filename<<std::endl;
    std::cout<<e.url_path<<std::endl;
    std::cout<<e.real_path<<std::endl;
    std::cout<<e.file_size<<std::endl;
    std::cout<<e.back_time<<std::endl;
    std::cout<<e.pack_flag<<std::endl;
    std::cout<<e.pack_path<<std::endl;
  }
  cloud::FileInfo e;
  data.SelectOne("/download/hello.txt",&e);
  std::cout<<e.filename<<std::endl;
  std::cout<<e.url_path<<std::endl;
  std::cout<<e.real_path<<std::endl;
  std::cout<<e.file_size<<std::endl;
  std::cout<<e.back_time<<std::endl;
  std::cout<<e.pack_flag<<std::endl;
  std::cout<<e.pack_path<<std::endl;
  */
}
cloud::DataManager *_data;
void HotTest()
{
  _data=new cloud::DataManager();
  cloud::HotManager cloud;
  cloud.RunMudule();
}
void ServerTest()
{
  cloud::Server srv;
  srv.RunModule();
}
int main()
{
  _data=new cloud::DataManager();
  //FileUtilTest();
  //JsonTest();
  // CompressTest();
  //DataTest();
  //HotTest();
  //ServerTest();
  std::thread hot_thread(HotTest);
  std::thread srv_thread(ServerTest);
  
  hot_thread.join();
  srv_thread.join();
  return 0;
}
