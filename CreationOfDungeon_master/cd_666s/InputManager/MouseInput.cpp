#include "MouseInput.h"
#include "DxLib.h"
#include "../../Vector2D.h"

MouseInput::MouseInput()
{
    RegistRecords();
}



MouseInput::~MouseInput()
{
    Clear();
}


void MouseInput::RegistRecords()
{
    AddRecord(MouseButtonCode::MOUSE_L, MOUSE_INPUT_LEFT);
    AddRecord(MouseButtonCode::MOUSE_CENTER, MOUSE_INPUT_MIDDLE);
    AddRecord(MouseButtonCode::MOUSE_R, MOUSE_INPUT_RIGHT);
}


void MouseInput::AddRecord(MouseButtonCode code, int value)
{
    MouseData *data = new MouseData(code, value);
    _inputMap.insert(std::make_pair(code, data));
    _inputs.push_back(data);
}


void MouseInput::Update()
{
    //イヘ゛ントを取り出す
    //glfwPollEvents();
    
    int x = 0;
    int y = 0;

    GetMousePoint(&x, &y);
    _cursorPos.Set(x, y);

	int value = GetMouseInput();

    for (auto input : _inputs)
    {
        ButtonTypeInput &data = input->_inputData;
		int state = value & input->_inputCode;
		if (state != 0)
		{
			data.UpdateState(true);
		}
		else
		{
			data.UpdateState(false);
		}
        MouseTypeInputEvent &events = input->_inputEvents;
        events.Update(_cursorPos);
    }

    UpdateDoubleClickStaet();
}


void MouseInput::UpdateDoubleClickStaet()
{
    _hasDoubleClicked = false;

    //ダブルクリック検出
    if (_hasClicked)
        _countFromFirstClick++;

    if (ButtonDown(MouseInput::MouseButtonCode::MOUSE_L))
    {
        //初回クリック見検出なら
        if (!_hasClicked)
        {
            _hasClicked = true;
            _countFromFirstClick = 0;
        }
        //規定フレーム内にクリックを検出してるなら
        else if (_countFromFirstClick < 30)
        {
            _hasDoubleClicked = true;

            //カウントリセット
            _hasClicked = false;
            _countFromFirstClick = 0;
            return;
        }
    }

    //カウントリセット
    if (_countFromFirstClick == 30)
    {
        _hasClicked = false;
        _countFromFirstClick = 0;
    }
}


void MouseInput::Clear()
{
    for (auto input : _inputs)
    {
        MouseTypeInputEvent &events = input->_inputEvents;
        events.ClearEventsAll();
    }
}