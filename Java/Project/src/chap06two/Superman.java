package chap06two;

public class Superman extends Human implements IFly {
    @Override
    public void fly() {
        System.out.println("슈퍼맨이 날아요");
    }
}
