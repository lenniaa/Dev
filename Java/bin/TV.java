public class TV extends Product {

    // TV의 특성
    private int inch;
    private String displayType;

    public TV(int productNum, String name, int price, int stock, int inch, String displayType) {
        super(productNum, name, price, stock);
        this.inch = inch;
        this.displayType = displayType;
    }

    public int getInch() {
        return inch;
    }

    @Override
    public String toString() {
        return "TV { Product Number=" + super.getProductNum() +
                ", Name=" + super.getName() +
                ", Price=" + super.getPrice() +
                ", Stock=" + super.getStock() +
                ", Inch=" + inch +
                ", Display Type=" + displayType +
                '}';
    }
}
