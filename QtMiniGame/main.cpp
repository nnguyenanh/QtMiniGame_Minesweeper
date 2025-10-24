#include "stdafx.h"
#include "QtMiniGame.h"
#include "DialogSignIn.h"
#include <QtWidgets/QApplication>
#include <QMediaPlayer>
#include <QAudioOutput>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// setup sound
	QMediaPlayer player_click;
	QAudioOutput audio_click;
	player_click.setAudioOutput(&audio_click);
	player_click.setSource(QUrl("qrc:/QtMiniGame/sounds/sound_4_click.mp3"));
	audio_click.setVolume(1.0);

	while (true)
	{
		{
			DialogSignIn sign_in;
			if (sign_in.exec() != QDialog::Accepted)
				break;
			player_click.play();
			sign_in.close();
		}
		{
			QtMiniGame game;
			game.show();

			QObject::connect(&game, &QtMiniGame::requestLogout, [&]() {
				if (game.isSound()) player_click.play();
				game.close();
				app.exit(9999);
				});

			int code = app.exec();

			if (code == 0)
			{
				break;
			}
			else if (code == 9999)
			{
				continue;
			}
		}
	}

	return 0;
}
