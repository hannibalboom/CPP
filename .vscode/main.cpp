#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
// 定义障碍物状态枚举
enum class obstacle_position {
    NONE,
    FRONT,
    RIGHT_FRONT,
    LEFT_FRONT
};

// 学生信息类
class Student {
public:
    Student() {}
    Student(string id, string name) : studentId(id), studentName(name) {}

    void setStudentId(string id) {
        studentId = id;
    }

    void setStudentName(string name) {
        studentName = name;
    }

    void print() {
        cout << "学号：" << studentId << std::endl;
        cout << "姓名：" << studentName << std::endl;
    }

    void save() {
        ofstream file("studentInfo.txt", std::ios::app);
        file << studentId << "," << studentName << std::endl;
        file.close();
    }

private:
    string studentId;
    string studentName;
};

// 抽象观察者类
class Observer {
public:
    virtual void update(obstacle_position position) = 0;
};

// 智能小车类
class SmartCar {
public:
    SmartCar() {}
    SmartCar(int id) : carId(id) {}

    void setID(int id) {
        carId = id;
    }

    void print() {
        cout << "智能小车编号：" << carId << std::endl;
        chassis.print();
        for (int i = 0; i < 4; i++) {
            tires[i].print();
        }
        agxKit.print();
        binocularCamera.print();
        gyroscope.print();
        lidar.print();
        lcd.print();
        battery.print();
        student.print();
    }

    void save() {
        ofstream file("smart_carInfo.txt", std::ios::app);
        file << carId << ",";
        chassis.save();
        for (int i = 0; i < 4; i++) {
            tires[i].save();
        }
        agxKit.save();
        binocularCamera.save();
        gyroscope.save();
        lidar.save();
        lcd.save();
        battery.save();
        student.save();
        file << std::endl;
        file.close();
    }

public:
    int carId;
    // 底盘类
    class Chassis : public Observer {
    public:
        Chassis() {}
        Chassis(string id, string model, int wheelbase, int trackWidth, int min_ground_clearance, int min_turn_radius, string driveForm, int max_travel) :
            chassis_id(id), model(model), wheelbase(wheelbase), trackWidth(trackWidth), min_ground_clearance(min_ground_clearance), min_turn_radius(min_turn_radius), driveForm(driveForm), max_travel(max_travel) {}

        void setChassis_id(string id) {
            chassis_id = id;
        }

        void setModel(string model) {
            this->model = model;
        }

        void setWheelbase(int wheelbase) {
            this->wheelbase = wheelbase;
        }

        void setTrack_width(int trackWidth) {
            this->trackWidth = trackWidth;
        }

        void setMin_ground_clearance(int min_ground_clearance) {
            this->min_ground_clearance = min_ground_clearance;
        }

        void setMinTurningRadius(int min_turn_radius) {
            this->min_turn_radius = min_turn_radius;
        }

        void setDriveForm(string driveForm) {
            this->driveForm = driveForm;
        }

        void setMax_travel(int max_travel) {
            this->max_travel = max_travel;
        }

        void print() {
            cout << "底盘编号：" << chassis_id << std::endl;
            cout << "型号：" << model << std::endl;
            cout << "轴距：" << wheelbase << "mm" << std::endl;
            cout << "轮距：" << trackWidth << "mm" << std::endl;
            cout << "最小离地间隙：" << min_ground_clearance << "mm" << std::endl;
            cout << "最小转弯半径：" << min_turn_radius << "m" << std::endl;
            cout << "驱动形式：" << driveForm << std::endl;
            cout << "最大行程：" << max_travel << "KM" << std::endl;
        }

        void save() {
            std::ofstream file("chassisInfo.txt", std::ios::app);
            file << chassis_id << "," << model << "," << wheelbase << "," << trackWidth << "," << min_ground_clearance << "," << min_turn_radius << "," << driveForm << "," << max_travel << std::endl;
            file.close();
        }

        void update(obstacle_position position) override {
            switch (position) {
            case obstacle_position::FRONT:
                cout << "后退。。。" <<endl;
                break;
            case obstacle_position::RIGHT_FRONT:
                cout << "左转。。。" <<endl;
                break;
            case obstacle_position::LEFT_FRONT:
                cout << "右转。。。" <<endl;
                break;
            default:
                break;
            }
        }

    private:
        string chassis_id;
        string model;
        int wheelbase;
        int trackWidth;
        int min_ground_clearance;
        int min_turn_radius;
        string driveForm;
        int max_travel;
    } chassis;

    // 轮胎类
    class Tire {
    public:
        Tire() {}
        Tire(string model, int size) : tireModel(model), size(size) {}

        void setTireModel(string model) {
            tireModel = model;
        }
        void setSize(int size) {
            this->size = size;
        }
        void print() {
            cout << "轮胎型号：" << tireModel <<endl;
            cout << "尺寸：" << size << "mm" <<endl;
        }
        void save() {
            ofstream file("tireInfo.txt", std::ios::app);
            file << tireModel << "," << size << std::endl;
            file.close();
        }
    private:
        string tireModel;
        int size;
    } tires[4];

    // AGX套件
    class AGXKit {
    public:
        AGXKit() {}
        AGXKit(string model, int ai, int cudaCores, int tensorCores, int vram, int storage) :
            model(model), ai(ai), cudaCores(cudaCores), tensorCores(tensorCores), vram(vram), storage(storage) {}

        void setModel(string model) {
            this->model = model;
        }
        void setAI(int ai) {
            this->ai = ai;
        }
        void setCudaCores(int cudaCores) {
            this->cudaCores = cudaCores;
        }
        void setTensorCores(int tensorCores) {
            this->tensorCores = tensorCores;
        }
        void setVram(int vram) {
            this->vram = vram;
        }
        void setStorage(int storage) {
            this->storage = storage;
        }
        void print() {
            cout << "AGX 套件型号：" << model << std::endl;
            cout << "AI 性能：" << ai << " TOPS" << std::endl;
            cout << "CUDA 核心数：" << cudaCores << std::endl;
            cout << "Tensor CORE：" << tensorCores << std::endl;
            cout << "显存为：" << vram << "G" << std::endl;
            cout << "存储：" << storage << "G" << std::endl;
        }
        void save() {
            std::ofstream file("agx_kitInfo.txt", std::ios::app);
            file << model << "," << ai << "," << cudaCores << "," << tensorCores << "," << vram << "," << storage << std::endl;
            file.close();
        }
    public:
        string model;
        int ai;
        int cudaCores;
        int tensorCores;
        int vram;
        int storage;
    } agxKit;
    // 双目摄像头类
    class BinocularCamera {
    public:
        BinocularCamera() {}
        BinocularCamera(string model, string camera, int rgb_resolution_width, int rgbResolutionHeight, int rgbFrameRate, int fovWidth, int fovHeight) :
            model(model), camera(camera), rgb_resolution_width(rgb_resolution_width), rgbResolutionHeight(rgbResolutionHeight), rgbFrameRate(rgbFrameRate), fovWidth(fovWidth), fovHeight(fovHeight) {}

        void setModel(string model) {
            this->model = model;
        }
        void setCamera(string camera) {
            this->camera = camera;
        }
        void setRGB_resolution_width(int width) {
            rgb_resolution_width = width;
        }
        void setRGB_resolution_height(int height) {
            rgbResolutionHeight = height;
        }
        void setRGB_frameRate(int rate) {
            rgbFrameRate = rate;
        }
        void setFOV_width(int width) {
            fovWidth = width;
        }
        void setFOV_height(int height) {
            fovHeight = height;
        }
        void print() {
            cout << "双目摄像头型号：" << model << std::endl;
            cout << "摄像头：" << camera << std::endl;
            cout << "RGB 帧分辨率：" << rgb_resolution_width << "x" << rgbResolutionHeight << std::endl;
            cout << "RGB 帧率：" << rgbFrameRate << std::endl;
            cout << "视场角：" << fovWidth << "x" << fovHeight << std::endl;
        }
        void save() {
            ofstream file("binocular_cameraInfo.txt", std::ios::app);
            file << model << "," << camera << "," << rgb_resolution_width << "," << rgbResolutionHeight << "," << rgbFrameRate << "," << fovWidth << "," << fovHeight << std::endl;
            file.close();
        }
    public:
        string model;
        string camera;
        int rgb_resolution_width;
        int rgbResolutionHeight;
        int rgbFrameRate;
        int fovWidth;
        int fovHeight;
    } binocularCamera;
    // 9 轴陀螺仪
    class Gyroscope {
    public:
        Gyroscope() {}
        Gyroscope(string model, string manufacturer) : model(model), manufacturer(manufacturer) {}

        void setModel(string model) {
            this->model = model;
        }

        void setManufacturer(string manufacturer) {
            this->manufacturer = manufacturer;
        }

        void print() {
            cout << "9 轴陀螺仪型号：" << model << std::endl;
            cout << "厂家：" << manufacturer << std::endl;
        }

        void save() {
            std::ofstream file("gyroscopeInfo.txt", std::ios::app);
            file << model << "," << manufacturer << std::endl;
            file.close();
        }
    private:
        string model;
        string manufacturer;
    } gyroscope;
    // 多线激光雷达
    class Lidar {
    public:
        Lidar() {}
        Lidar(string model, int channels, int range, int power) : model(model), channels(channels), range(range), power(power) {}

        void setModel(string model) {
            this->model = model;
        }
        void setChannels(int channels) {
            this->channels = channels;
        }
        void setRange(int range) {
            this->range = range;
        }
        void setPower(int power) {
            this->power = power;
        }
        void print() {
            cout << "多线激光雷达型号：" << model << std::endl;
            cout << "通道数：" << channels << std::endl;
            cout << "测试范围：" << range << "m" << std::endl;
            cout << "功耗：" << power << "W" << std::endl;
        }

        void save() {
            std::ofstream file("lidarInfo.txt", std::ios::app);
            file << model << "," << channels << "," << range << "," << power << std::endl;
            file.close();
        }

        // 更新方法
        void update_obstacle(obstacle_position position) {
            for (auto observer : observers) {
                observer->update(position);
            }
        }

        // 添加观察者
        void addObserver(Observer* observer) {
            observers.push_back(observer);
        }

    private:
        string model;
        int channels;
        int range;
        int power;
        vector<Observer*> observers;
    };

    // 液晶显示屏
    class LCD {
    public:
        LCD() {}
        LCD(int size, string model) : size(size), model(model) {}

        void setSize(int size) {
            this->size = size;
        }

        void setModel(string model) {
            this->model = model;
        }

        void print() {
            cout << "液晶显示屏尺寸：" << size << std::endl;
            cout << "型号：" << model << std::endl;
        }

        void save() {
            std::ofstream file("lcdInfo.txt", std::ios::app);
            file << size << "," << model << std::endl;
            file.close();
        }

    private:
        int size;
        string model;
    } lcd;

    // 电池模块类
    class batteryMode {
    public:
        batteryMode() {}
        batteryMode(string parameter, int power_supply, int charging_time) : parameter(parameter), power_supply(power_supply), charging_time(charging_time) {}

        void setParameters(string parameter) {
            this->parameter = parameter;
        }

        void setPower_supply(int power_supply) {
            this->power_supply = power_supply;
        }

        void setCharging_time(int charging_time) {
            this->charging_time = charging_time;
        }

        void print() {
            cout << "电池参数：" << parameter << std::endl;
            cout << "对外供电：" << power_supply << "V" << std::endl;
            cout << "充电时长：" << charging_time << "H" << std::endl;
        }

        void save() {
            std::ofstream file("batteryInfo.txt", std::ios::app);
            file << parameter << "," << power_supply << "," << charging_time << std::endl;
            file.close();
        }

    private:
        string parameter;
        int power_supply;
        int charging_time;
    } battery;

    Student student;

public:
    Lidar lidar;
};
// // 初始化学生信息
// vector<Student> initStudents() {
//     vector<Student> init_students = {
//         {"20230001", "张三"},
//         {"20230002", "李四"},
//         {"20230003", "王五"},
//         {"20230004", "赵六"},
//         {"20230005", "孙七"},
//         {"20230006", "周八"},
//         {"20230007", "吴九"},
//         {"20230008", "郑十"},
//         {"20230009", "黄十一"},
//         {"20230010", "刘十二"}
//     };
//     return students;
// }
int main() {
    // 创建智能小车数组和学生数组
    SmartCar cars[10];
    Student students[10];
    // 初始化学生信息
    for (int i = 0; i < 10; i++) {
        students[i] = Student("E202100" + to_string(i + 1), "Student" + to_string(i + 1));
    }

    // 初始化智能小车信息
    for (int i = 0; i < 10; i++) {
        cars[i].setID(i + 1);
        cars[i].chassis.setChassis_id("dp" + std::to_string(i + 1) + "A");
        cars[i].chassis.setModel("SCOUT MINI");
        cars[i].chassis.setWheelbase(451);
        cars[i].chassis.setTrack_width(490);
        cars[i].chassis.setMin_ground_clearance(115);
        cars[i].chassis.setMinTurningRadius(0);
        cars[i].chassis.setDriveForm("四轮四驱");
        cars[i].chassis.setMax_travel(10);

        for (int j = 0; j < 4; j++) {
            cars[i].tires[j].setTireModel(j % 2 == 0 ? "公路轮" : "麦克纳姆轮");
            cars[i].tires[j].setSize(175);
        }

        cars[i].agxKit.setModel("AGX Xavier");
        cars[i].agxKit.setAI(32);
        cars[i].agxKit.setCudaCores(512);
        cars[i].agxKit.setTensorCores(64);
        cars[i].agxKit.setVram(32);
        cars[i].agxKit.setStorage(32);

        cars[i].binocularCamera.setModel("RealSense D435i");
        cars[i].binocularCamera.setCamera("D430");
        cars[i].binocularCamera.setRGB_resolution_width(1920);
        cars[i].binocularCamera.setRGB_resolution_height(1080);
        cars[i].binocularCamera.setRGB_frameRate(30);
        cars[i].binocularCamera.setFOV_width(87);
        cars[i].binocularCamera.setFOV_height(58);

        cars[i].gyroscope.setModel("CH110");
        cars[i].gyroscope.setManufacturer("NXP");

        cars[i].lidar.setModel("RS-Helios-16p");
        cars[i].lidar.setChannels(16);
        cars[i].lidar.setRange(100);
        cars[i].lidar.setPower(8);

        cars[i].lcd.setSize(11.6);
        cars[i].lcd.setModel("super");

        cars[i].battery.setParameters("24V/15Ah");
        cars[i].battery.setPower_supply(24);
        cars[i].battery.setCharging_time(2);

        cars[i].student = students[i];

        // 将底盘注册为激光雷达的观察者
        cars[i].lidar.addObserver(&cars[i].chassis);
    }

    // 保存所有小车信息
    for (int i = 0; i < 10; i++) {
        cars[i].save();
    }

    int current_car_index = 0;
    char input;
    while (true) {
        // 打印当前小车信息
        cars[current_car_index].print();
        cout << "按 'n' 查看下一辆小车信息，'p' 查看上一辆小车信息，或 'q' 退出: ";
        cin >> input;

        // 根据输入进行操作
        if (input == 'n') {
            if (current_car_index < 9) {
                current_car_index++;
            }
        }
        else if (input == 'p') {
            if (current_car_index > 0) {
                current_car_index--;
            }
        }
        else {
            break;
        }
    }

    // 模拟障碍物状态输入
    int obstacleInput;
    cout << "输入障碍物状态（1 代表前方障碍，2 代表左前方障碍，3 代表右前方障碍）：";
    cin >> obstacleInput;
    obstacle_position position;
    switch (obstacleInput) {
    case 1:
        position = obstacle_position::FRONT;
        break;
    case 2:
        position = obstacle_position::LEFT_FRONT;
        break;
    case 3:
        position = obstacle_position::RIGHT_FRONT;
        break;
    default:
        position = obstacle_position::NONE;
        break;
    }
    // 触发激光雷达更新障碍物状态
    cars[0].lidar.update_obstacle(position);

    cout << "按任意键继续";
    cin.get();
    return 0;
}