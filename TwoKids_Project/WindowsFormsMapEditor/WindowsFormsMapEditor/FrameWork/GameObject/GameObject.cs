using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

using Microsoft.DirectX.Direct3D;
using Microsoft.DirectX;

namespace Framework
{
    public class Transform
    {
        public Point position = new Point(0, 0);
        public Point rotationCenter = new Point(0, 0);
        public float angle = 0.0f;
        public Point scale = new Point(0, 0);

        public Transform(Point _position, Point _rotationCenter, float _angle, Point _scale)
        {
            position = _position;
            rotationCenter = _rotationCenter;
            angle = _angle;
            scale = _scale;
        }
        public Transform()
        {

        }
    }
    public class GameObject
    {
        protected Transform transform;
        protected Color color;
        protected Texture texture = null;

        public Point Position { get => transform.position; set => transform.position = value; }
        public Texture Texture { get => texture; set => texture = value; }

        public virtual void Init()
        {

        }
        public virtual void Update()
        {

        }
        public virtual void Render()
        {

        }
        public virtual void Release()
        {

        }
        public GameObject()
        {
            transform = new Transform();
            color = new Color();
            color = Color.White;
        }

        public bool IsCollision(Point m_size, Rectangle o_Rectangle)
        {
            if (Position.X < o_Rectangle.X &&
               Position.X + m_size.X > o_Rectangle.Width &&
               Position.Y < o_Rectangle.Y &&
               Position.Y + m_size.Y > o_Rectangle.Height) return true;
            return false;
        }

        public Rectangle GetMousePos()
        { 
            Rectangle mouse_Pos = new Rectangle();
            mouse_Pos.X = Cursor.Position.X - (int)(Main.MainGame.GetT.FormPosition.X + 1280 * 0.2)
                - ScrollManager.GetT.MainScrollPoint.X;
            mouse_Pos.Y = Cursor.Position.Y - Main.MainGame.GetT.FormPosition.Y - 24 
                - ScrollManager.GetT.MainScrollPoint.Y;
            mouse_Pos.Width = Cursor.Position.X - (int)(Main.MainGame.GetT.FormPosition.X + 1280 * 0.2)
                - ScrollManager.GetT.MainScrollPoint.X;
            mouse_Pos.Height = Cursor.Position.Y - Main.MainGame.GetT.FormPosition.Y - 24
                - ScrollManager.GetT.MainScrollPoint.Y;

            return mouse_Pos;
        }

        public Rectangle GetSubMousePos()
        {
            Rectangle mouse_Pos = new Rectangle();
            mouse_Pos.X = Cursor.Position.X - (int)(Main.MainGame.GetT.FormPosition.X + 50)
                - ScrollManager.GetT.SubScrollPoint.X;
            mouse_Pos.Y = Cursor.Position.Y - Main.MainGame.GetT.FormPosition.Y - 144
                - ScrollManager.GetT.SubScrollPoint.Y;
            mouse_Pos.Width = Cursor.Position.X - (int)(Main.MainGame.GetT.FormPosition.X + 50)
                - ScrollManager.GetT.SubScrollPoint.X;
            mouse_Pos.Height = Cursor.Position.Y - Main.MainGame.GetT.FormPosition.Y - 144
                - ScrollManager.GetT.SubScrollPoint.Y;

            return mouse_Pos;
        }
    }
}