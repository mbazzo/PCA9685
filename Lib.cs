using System.Runtime.InteropServices;

namespace PCA9685
{
    internal class Lib
    {
        internal const string Lib1 = "libPCA9685.so.0.1";

        [DllImport(Lib1, EntryPoint = "Setup", SetLastError = true)]
        public static extern void Init();

        [DllImport(Lib1, EntryPoint = "SetPwm", SetLastError = true)]
        public static extern void SetPwm(int on, int off, int channel);
    }
}
