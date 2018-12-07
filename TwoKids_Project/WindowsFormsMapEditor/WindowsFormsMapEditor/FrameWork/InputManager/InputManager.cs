using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

using Framework;

namespace Framework
{
    public class InputManager : Singleton<InputManager>
    {
        public Point GetStreamPoint(string str)
        {
            Point point = new Point(0, 0);
            int x = 0;
            int y = 0;

            string[] result = str.Split(' ');
            Int32.TryParse(result[0], out x);
            Int32.TryParse(result[1], out y);
            point.X = x; point.Y = y;
            return point;
        }
        public Point GetStreamPoint(StreamReader streamReader, ref string tileName, ref string tileState)
        {
            Point point = new Point(0, 0);

            string line = streamReader.ReadLine();
            int i = 0;
            tileState = line.Split(' ')[0];
            tileName = line.Split(' ')[1];

            string pointLine = "";
            for( ; i < line.Length; i++)
            {
                pointLine += line[i].ToString();
            }
            point = GetStreamPoint(pointLine);
            return point;
        }
    }
}