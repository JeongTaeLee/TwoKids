using System;
using System.Collections.Generic;
using System.IO;

using Microsoft.DirectX.Direct3D;
using System.Drawing;

using Framework.Main;
using DxBasic;

namespace Framework 
{
    public class ResourceManager : Singleton<ResourceManager>
    {
        private Dictionary<string, Texture> d_Texture = new Dictionary<string, Texture>();
        private Dictionary<string, Texture> s_Texture = new Dictionary<string, Texture>();

        public Texture GetTexture(string route, Device device)
        {
            var _textureList = d_Texture;
            if (device == MainGame.GetT.tileDX.Dx_device) _textureList = s_Texture;

            if (_textureList.ContainsKey(route)) return _textureList[route];
            Image image = new Bitmap(route);

            Texture tex = TextureLoader.FromFile(device, route,
                image.Width, image.Height, 0, Usage.None, Format.A8R8G8B8,
                Pool.Managed, Filter.Linear, Filter.None, 0);
            _textureList[route] = tex;
            
            return tex;
        }
    }
}