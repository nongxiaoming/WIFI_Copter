#ifndef PREVIEW360_H
#define PREVIEW360_H

#include "xpushbutton.h"
#include "xlabel.h"
#include "common.h"

class CharacterWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CharacterWidget(QWidget *parent = 0);
	~CharacterWidget();
	void translateLanguage();

	enum EButtonMouseState
	{
		EButtonMouseDefault = 0,
		EButtonMouseEnter,
		EButtonMousePress,
		EButtonMouseNone
	};

protected:

	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void keyPressEvent(QKeyEvent *);

private slots:

    void changeCurrentPage(XLabel *);

private:

	void changeCurrentButton();
	void setLabelMove(bool);
	void moveCurrentPage(bool);

	QStringList name_list;
	QPoint m_mouseSrcPos;
	QPoint m_mouseDstPos;
	int current_pos_x;
	bool mouse_press;
	bool mouse_move;
	bool label_move;

	QLabel *background_label; //����ͼƬ
	int current_index; //��ǰͼƬ�±�
	QLabel *total_label; //ͼƬ������壩
    XLabel *label_array[4]; //�洢ͼƬ������
    XPushButton *close_button; //�رհ�ť
};

#endif // PREVIEW360_H