#ifndef Texture2D_h
#define Texture2D_h

#include <vector>
#include <memory>
#include "../Resources/Resource.h"
#include "../Color.h"
#include "../../Vector2D.h"

class Camera;

class Texture2D : public std::enable_shared_from_this<Texture2D>
{
    friend class GraphArray;
public:
    Texture2D(int handle);
    virtual ~Texture2D();

    enum class RenderType
    {
        DEFAULT,
        UI
    };
    
    enum class AnchorType
    {
        CENTER,
        UPPER_LEFT
    };
    
    void SetPosition(Vector2D pos){ _pos = pos; }
    void BuildTextureWithInit(int handle, int width, int height);
    void BuildTexture(Vector2D pos, int width, int height);
    void BuildTexture(Vector2D pos, int width, int height, Vector2D scale);
    void Render(const Camera& camera);

    //テクスチャの元サイズ
    Vector2D GetSize() const
    {
        return Vector2D(_baseSize._x / _scale._x, _baseSize._y / _scale._y);
    }
    
    //テクスチャに拡大率を加味した画面上の表示サイズ
    Vector2D GetBaseSize() const { return _baseSize; }
    //拡大率
    Vector2D GetScale() const { return _scale; }
    void SetScale(Vector2D scale) { _scale = scale; };

    int GetHandle() const { return _handle; }
    RenderType GetRenderType() const { return _type; }
    void SetRenderType(RenderType type);

    AnchorType GetAnchorType() const { return _anchorType; }
    void SetAnchorType(AnchorType type) { _anchorType = type; };
    
    int GetPriority() const { return _priority; }
    void SetPriority(int priority);
    
    void SetBaseColor(Color4 color){ _baseColor = color; }
    void SetDisplayMode(bool isDisplaying) { _isDisplaying = isDisplaying; }

    //テクスチャの使用する領域を(0 ~ 1.0)で指定する
    void SetUVArea(Vector2D ul, Vector2D lr)
    {
        _usingUV_ul = ul;
        _usingUV_lr = lr;
    };
    
    double _angle;
    
protected:

    //描画時にOpenGLに通達するテクスチャ番号
    int _handle;

    //テクスチャの基本色(乗算される色)
    Color4 _baseColor;
    
    //各軸方向への拡大率
    Vector2D _scale;

    //左下座標
    Vector2D _pos;

    //拡大率とテクスチャの大きさを合わせた画面上での大きさ
    Vector2D _baseSize;
    
    
    //使用するテクスチャの領域(0 ~ 1.0)
    Vector2D _usingUV_ul;
    Vector2D _usingUV_lr;
    
    //レンダリングするかどうか(一時的非表示用)
    bool _isDisplaying;
    
    //レンダリング時にどのカメラに写すか
    RenderType _type;
    
    //中心座標の位置
    AnchorType _anchorType;
    
    //描画優先順位
    int _priority;
};

#endif /* Texture2D_h */
