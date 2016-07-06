using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassifiedByTime
{
    class Program
    {
        static void Main(string[] args)
        {
            string rootDir = Directory.GetCurrentDirectory();
            Console.Write("Root Dir: ");
            Console.WriteLine(rootDir);
            DirectoryInfo rootDirInfo = new DirectoryInfo(rootDir);
            foreach (FileInfo fileInfoTemp in rootDirInfo.GetFiles())
            {
                if (fileInfoTemp.Name.Contains("ClassifiedByTime"))
                    continue;
                Console.WriteLine(fileInfoTemp.Name);
                DateTime LastWriteDateTime = fileInfoTemp.LastWriteTime;

                string newPathName = LastWriteDateTime.ToString("yyyy_MM_dd");

                newPathName = rootDir + "\\" + newPathName;

                if (!Directory.Exists(newPathName))
                    Directory.CreateDirectory(newPathName);

                string oldPathName = rootDir + "\\" + fileInfoTemp.Name;
                newPathName = newPathName + "\\" + fileInfoTemp.Name;

                File.Move(oldPathName, newPathName);
            }

            Console.ReadLine();
        }
    }
}
