using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Framework
{
    public class Singleton<T> where T : class, new()
    {
        private static T instance = default(T);

        public static T GetT
        {
            get
            {
                if (instance == null) instance = new T();
                return instance;
            }
        }
    }
}