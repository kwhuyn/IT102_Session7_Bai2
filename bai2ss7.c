#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;
    float ratedPowerKW;
};

struct EnergySensor {
    float voltageVolts;
    float currentAmperes;
    int unoccupancyMinutes;
};

int main() {
    struct SmartDevice device;
    struct EnergySensor sensor;
    float operatingHours;

    printf("Nhap ma dinh danh thiet bi: ");
    if (scanf("%d", &device.deviceID) != 1) return 0;

    printf("Nhap ten thiet bi: ");
    scanf("%s", device.deviceName);

    printf("Nhap trang thai hoat dong (1: Bat, 0: Tat): ");
    if (scanf("%d", &device.status) != 1) return 0;

    printf("Nhap cong suat dinh muc (kW): ");
    if (scanf("%f", &device.ratedPowerKW) != 1) return 0;

    printf("Nhap dien ap do duoc (V): ");
    if (scanf("%f", &sensor.voltageVolts) != 1) return 0;

    printf("Nhap dong dien do duoc (A): ");
    if (scanf("%f", &sensor.currentAmperes) != 1) return 0;

    printf("Nhap thoi gian vang nguoi (phut): ");
    if (scanf("%d", &sensor.unoccupancyMinutes) != 1) return 0;

    printf("Nhap so gio van hanh trong thang (gio): ");
    if (scanf("%f", &operatingHours) != 1) return 0;

    if (sensor.voltageVolts < 0.0f || sensor.currentAmperes < 0.0f || sensor.unoccupancyMinutes < 0) {
        printf("\n[LOI] Thong so cam bien bat thuong (gia tri am). Huy thao tacs xu ly!\n");
        return 0;
    }

    if (operatingHours <= 0.0f || operatingHours > 744.0f) {
        printf("\n[LOI] So gio van hanh trong thang khong hop le (0 < hours <= 744). Tu choi tinh toan!\n");
        return 0;
    }

    if (sensor.currentAmperes > 30.0f) {
        device.status = 0;
        printf("\n[CANH BAO] Dong dien vuot nguong an toan (>30.0A)! Kich hoa ngat khan cap, tat thiet bi.\n");
    } else if (device.status == 1 && sensor.unoccupancyMinutes >= 15) {
        device.status = 0;
        printf("\n[THONG BAO] Phong trong lien tuc >= 15 phut. Tu dong tat thiet bi de tiet kiem dien.\n");
    }

    float totalKWh = device.ratedPowerKW * operatingHours * (device.status == 1 ? 1.0f : 0.0f);
    
    float totalCost = 0.0f;
    float remainingKWh = totalKWh;

    if (remainingKWh > 0.0f) {
        float k1 = (remainingKWh < 50.0f) ? remainingKWh : 50.0f;
        totalCost += k1 * 1806.0f;
        remainingKWh -= k1;
    }
    if (remainingKWh > 0.0f) {
        float k2 = (remainingKWh < 50.0f) ? remainingKWh : 50.0f;
        totalCost += k2 * 1866.0f;
        remainingKWh -= k2;
    }
    if (remainingKWh > 0.0f) {
        float k3 = (remainingKWh < 100.0f) ? remainingKWh : 100.0f;
        totalCost += k3 * 2167.0f;
        remainingKWh -= k3;
    }
    if (remainingKWh > 0.0f) {
        totalCost += remainingKWh * 2729.0f;
    }

    printf("\n==================================================\n");
    printf("         BAO CAO QUAN LY NAG LUONG SMART HOME     \n");
    printf("==================================================\n");
    printf("Ma thiet bi     : %d\n", device.deviceID);
    printf("Ten thiet bi    : %s\n", device.deviceName);
    printf("Trang thai cuoi : %s\n", (device.status == 1 ? "Dang bat" : "Da tat"));
    printf("Cong suat       : %.2f kW\n", device.ratedPowerKW);
    printf("Dien ap do      : %.2f V\n", sensor.voltageVolts);
    printf("Dong dien do    : %.2f A\n", sensor.currentAmperes);
    printf("Thoi gian vang  : %d phut\n", sensor.unoccupancyMinutes);
    printf("--------------------------------------------------\n");
    printf("Tong dien nang  : %.2f kWh\n", totalKWh);
    printf("Tong tien dien  : %.2f VNĐ (Chua VAT)\n", totalCost);
    printf("==================================================\n");

    return 0;
}