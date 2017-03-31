#include <Log.h>
Log::Log()
{

}

Log::~Log()
{
	google::ShutdownGoogleLogging();
}

bool Log::Init(char * name)
{
	google::InitGoogleLogging(name);
	FLAGS_log_dir = "./log";
	//FLAGS_logtostderr = true;
	FLAGS_alsologtostderr = true;
	FLAGS_colorlogtostderr = true;//�����������Ļ����־��ʾ��Ӧ��ɫ
	FLAGS_logbufsecs = 0; //������־�����Ĭ��Ϊ30�룬�˴���Ϊ�������
	FLAGS_max_log_size = 10;	//�����־��С��MB��

	//google::SetStderrLogging(google::INFO); //���ü������ google::INFO ����־ͬʱ�������Ļ
	//google::SetLogDestination(google::ERROR,"log/error_");    //���� google::ERROR �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::INFO, "./log/INFO_"); //���� google::INFO �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::WARNING, "./log/WARNING_");   //���� google::WARNING �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::ERROR, "./log/ERROR_");   //���� google::ERROR �������־�洢·�����ļ���ǰ׺
	
	FLAGS_stop_logging_if_full_disk = true;	//�����̱�д��ʱ��ֹͣ��־���
	google::SetLogFilenameExtension("game_");	//�����ļ�����չ����ƽ̨����������Ҫ���ֵ���Ϣ
	//google::InstallFailureSignalHandler();	//��׽ core dumped  glog-0.3.3\src\signalhandler.cc ��߽�����ʵ�� ������ļ� �ӵ� ������ ����һ�¾Ϳ�����

	LOG(INFO) << "glog init success" << endl;
	return true;
}

