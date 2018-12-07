using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

using Framework;

namespace Framework
{
    public class ScrollManager : Singleton<ScrollManager>
    {
        private Point point = new Point(0, 0);
        public Point MainScrollPoint { get => point; set => point = value; }

        private Point subPoint = new Point(0, 0);
        public Point SubScrollPoint { get => subPoint; set => subPoint = value; }
        int speed = new int();
        public int Speed { get => speed; set => speed = value; }

        public void ScrollUp()
        {
            point.Y += speed;
        }
        public void ScrollDown()
        {
            point.Y -= speed;  
        }
        public void ScrollLeft()
        {
            point.X += speed;
        }
        public void ScrollRight()
        {
            point.X -= speed;
        }
        public void Update()
        {

        }
        public ScrollManager()
        {
            speed = 6;
        }
    }
}