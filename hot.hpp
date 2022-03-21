#ifndef __MY_HOT__
#define __MY_HOT__ 
#include<unistd.h>
#include"data.hpp"

extern cloud::DataManager *_data;//全局数据

namespace cloud
{
  class HotManager
  {
    private:
      time_t _hot_time=30;//热点判断时长，应该是个可配置项，当前简化，默认30s
      std::string _backup_dir="./backup_dir/";//要检测的源文件的储存路径
    public:
      HotManager()
      {
        FileUtil(_backup_dir).CreateDirectory();
      }
      bool IsHot(const std::string &filename)
      {
        time_t atime=FileUtil(filename).Atime();
        time_t ctime=time(NULL);
        if((ctime-atime)>_hot_time)
        {
          return false;
        }
        return true;
      }
      bool RunMudule()
      {
        while(1)
        {
          //1.遍历目录
          std::vector<std::string> arry;
          FileUtil(_backup_dir).ScanDirectory(&arry);
          //2.遍历信息
          for(auto &file : arry)
          {
            //3.获取指定文件时间属性，以当前系统时间进行热点判断
            if(IsHot(file)==true)
            {
              continue;//热点文件暂时不处理
            }
            //3.5 获取当前文件的历史信息
            FileInfo info;
            bool ret=_data->SelectOneByRealpath(file,&info);
            if(ret==false)
            {
              //如果当前文件没有历史信息 这可能是一个异常上传的文件，删除处理
              std::cout<<"An exception file is detected.Delect it!\n";
              FileUtil(file).Remove();
            }
            //4.非热点进行压缩存储
            FileUtil(file).Compress(info.pack_path);
            //5.压缩后进行备份信息修改
            _data->UpdateStatus(file,true);
            std::cout<<info.real_path<<"<--compress-->"<<info.pack_path<<std::endl;
          }
          usleep(1000);//避免空目录下 空遍历消耗CPU资源过高
        }
        return true;
      }
  };
}



#endif
