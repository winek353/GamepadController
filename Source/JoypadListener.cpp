#include "JoypadListener.hpp"
#include "SystemController.hpp"

JoypadListener::JoypadListener()
{
  QDir deviceDir("/dev/input");
  QStringList devices = deviceDir.entryList(QStringList("js*"), QDir::System );
  QRegExp devicename(".*\\js(\\d+)");
  int joydev = -1;
    
  for (QStringList::Iterator it = devices.begin(); it != devices.end(); ++it)
  {
    cout << "found a device file, " << qPrintable("/" + (*it)) << endl;
     
    joydev = open( qPrintable("/dev/input/" + (*it)), O_RDONLY | O_NONBLOCK);
      
    if (joydev > 0)
    {
      devicename.indexIn(*it);
      int index = QString(devicename.cap(1)).toInt();
	
      int axes = 0;
      ioctl (joydev, JSIOCGAXES, &axes);
	
      int buttons = 0;
      ioctl (joydev, JSIOCGBUTTONS, &buttons);
      cout << "udalo sie otworzyc!!! ten joypad ma " << axes << " osi, oraz " << buttons << " przyciskow" << endl;
      
      if(axes >= 6 && buttons >= 15)
      {
	cout << "Ten jest OK - bierzemy!" << endl;
	break;
      }
    }
  }
  
  if(joydev > 0)
  {
    joydevFileHandle = new QSocketNotifier(joydev, QSocketNotifier::Read, this);
    connect(joydevFileHandle, SIGNAL(activated(int)), this, SLOT(handleJoyEvents(int)));
    dev = joydev;
    
    handler = new JoypadHandler(new SystemController);
    
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerCalled()));
    timer->start(10);
  }
  else
  {
    cout << "Nie ma odpowiedniego pada :(" << endl;
  }
}

void JoypadListener::handleJoyEvents(int fd)
{
  js_event msg;
  int len;

  len = read( dev, &msg, sizeof(js_event));
  if (len == (int) sizeof(js_event))
  {
    if(msg.type & JS_EVENT_AXIS)
    {
      handleAxis(msg.number, msg.value);
    }
    else
    {
      handleButton(msg.number, msg.value);
    }
  }
}

void JoypadListener::handleButton(int nb,int value)
{
  PressedOrReleased pressedOrReleased= (value==1) ? PRESSED : RELEASED;

  switch(nb)
  {
    case 0: handler->handleButton(BUTTON_A, pressedOrReleased);  break;
    case 1: handler->handleButton(BUTTON_B, pressedOrReleased);  break;
    case 2: handler->handleButton(BUTTON_X, pressedOrReleased);  break;
    case 3: handler->handleButton(BUTTON_Y, pressedOrReleased);  break;
    case 4: handler->handleButton(BUTTON_LB, pressedOrReleased); break;
    case 5: handler->handleButton(BUTTON_RB, pressedOrReleased); break;  
    case 6: handler->handleButton(BUTTON_BACK, pressedOrReleased); break;
    case 7: handler->handleButton(BUTTON_START, pressedOrReleased); break;
    case 8: handler->handleButton(BUTTON_XBOX, pressedOrReleased); break;
    case 9: handler->handleButton(BUTTON_LEFT_JOY, pressedOrReleased); break;
    case 10: handler->handleButton(BUTTON_RIGHT_JOY, pressedOrReleased); break;
    case 11: handler->handleButton(BUTTON_LEFT, pressedOrReleased); break;
    case 12: handler->handleButton(BUTTON_RIGHT, pressedOrReleased); break;
    case 13: handler->handleButton(BUTTON_UP, pressedOrReleased); break;
    case 14: handler->handleButton(BUTTON_DOWN, pressedOrReleased); break;
  }
}

void JoypadListener::handleAxis(int nb,int value)
{
  switch(nb)
  {
    case 0: handler->handleAxis(AXIS_LEFT_HORIZONTAL, value);break;
    case 1: handler->handleAxis(AXIS_LEFT_VERTICAL, value);break;
    case 2: handler->handleAxis(AXIS_LT, value);break;
    case 3: handler->handleAxis(AXIS_RIGHT_HORIZONTAL, value);break;
    case 4: handler->handleAxis(AXIS_RIGHT_VERTICAL, value);break;
    case 5: handler->handleAxis(AXIS_RT, value);break;
  }
}

void JoypadListener::timerCalled()
{
  handler->handleTime();
}
