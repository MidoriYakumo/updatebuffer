#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include <cmath>
#include <Qt3DRender/QBuffer>
#include <Qt3DLogic/QFrameAction>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QLatin1String("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	auto qmlApp = engine.rootObjects()[0];
	auto frameAction = qvariant_cast<Qt3DLogic::QFrameAction*>(qmlApp->property("frameAction"));
	auto buffer = qvariant_cast<Qt3DRender::QBuffer*>(qmlApp->property("vertexBuffer"));
	float t = 0;
	qmlApp->connect(frameAction, &Qt3DLogic::QFrameAction::triggered, [&](float dt)
	{
		t += dt * 30;
		QVector<float> vertex = {
			-0.5, -0.5, -0.5,  0.0, 0.0,
			 0.5, -0.5, -0.5,  1.0, 0.0,
			 0.5,  0.5, -0.5,  1.0, 1.0,
			 0.5,  0.5, -0.5,  1.0, 1.0,
			-0.5,  0.5, -0.5,  0.0, 1.0,
			-0.5, -0.5, -0.5,  0.0, 0.0,

			-0.5, -0.5,  0.5,  0.0, 0.0,
			 0.5, -0.5,  0.5,  1.0, 0.0,
			 0.5,  0.5,  0.5,  1.0, 1.0,
			 0.5,  0.5,  0.5,  1.0, 1.0,
			-0.5,  0.5,  0.5,  0.0, 1.0,
			-0.5, -0.5,  0.5,  0.0, 0.0,

			-0.5,  0.5,  0.5,  1.0, 0.0,
			-0.5,  0.5, -0.5,  1.0, 1.0,
			-0.5, -0.5, -0.5,  0.0, 1.0,
			-0.5, -0.5, -0.5,  0.0, 1.0,
			-0.5, -0.5,  0.5,  0.0, 0.0,
			-0.5,  0.5,  0.5,  1.0, 0.0,

			 0.5,  0.5,  0.5,  1.0, 0.0,
			 0.5,  0.5, -0.5,  1.0, 1.0,
			 0.5, -0.5, -0.5,  0.0, 1.0,
			 0.5, -0.5, -0.5,  0.0, 1.0,
			 0.5, -0.5,  0.5,  0.0, 0.0,
			 0.5,  0.5,  0.5,  1.0, 0.0,

			-0.5, -0.5, -0.5,  0.0, 1.0,
			 0.5, -0.5, -0.5,  1.0, 1.0,
			 0.5, -0.5,  0.5,  1.0, 0.0,
			 0.5, -0.5,  0.5,  1.0, 0.0,
			-0.5, -0.5,  0.5,  0.0, 0.0,
			-0.5, -0.5, -0.5,  0.0, 1.0,

			-0.5,  0.5, -0.5,  0.0, 1.0,
			 0.5,  0.5, -0.5,  1.0, 1.0,
			 0.5,  0.5,  0.5,  1.0, 0.0,
			 0.5,  0.5,  0.5,  1.0, 0.0,
			-0.5,  0.5,  0.5,  0.0, 0.0,
			-0.5,  0.5, -0.5,  0.0, 1.0,
		};
		for (uint i = 0; i < 36; ++i)
		{
			vertex[i*5+0] += sin((i + t + 1) * 1e-1) * 1e1 / exp(t * 1e-1);
			vertex[i*5+1] += cos((i + t + 2) * 1e-1) * 1e1 / exp(t * 1e-1);
			vertex[i*5+2] += sin((i + t + 3) * 1e-1) * 1e1 / exp(t * 1e-1);
		}
		buffer->updateData(0, QByteArray::fromRawData(
							   reinterpret_cast<const char*>(vertex.constData()),
							   vertex.size() * sizeof(float)));
	});

	return app.exec();
}
