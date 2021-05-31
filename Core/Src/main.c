/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lib/UL/spinner/spinner.h"
#include "lib/UL/button_controler/button_controler.h"
#include "lib/drivers/uart/uart.h"
#include "lib/UL/io/io_generic/io_generic.h"
#include "lib/UL/io/io_uart/io_uart.h"
#include "lib/UL/io/io_spi/io_spi.h"
#include "lib/UL/io/io_i2c/io_i2c.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* Definitions for defaultTask */
xTaskHandle defaultTaskHandle;
/* Definitions for spinner_task */
xTaskHandle spinner_taskHandle;
/* Definitions for button_task */
xTaskHandle button_taskHandle;
/* Definitions for io_generic_task */
xTaskHandle io_generic_taskHandle;

/* Definitions for spinner_queue_handle */
xQueueHandle spinner_queue_handle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void *pvParameters);
void spinner_task_entry(void *pvParameters);
void button_task_entry(void *pvParameters);
void io_generic_task_entry(void *pvParameters);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    /* USER CODE BEGIN 2 */
    /* USER CODE END 2 */
    /* Init scheduler */
    osKernelInitialize();

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    spinner_queue_handle = xQueueCreate(2, sizeof(uint32_t));
    /* USER CODE END RTOS_QUEUES */
    /* Create the thread(s) */
    /* creation of defaultTask */
    xTaskCreate(StartDefaultTask, "defaultTask", 128 * 4, NULL,  1 | portPRIVILEGE_BIT, defaultTaskHandle);
    /* creation of spinner_task */
    xTaskCreate(spinner_task_entry, "spinner_task", 128 * 4, NULL,  4 | portPRIVILEGE_BIT, spinner_taskHandle);
    /* creation of button_task */
    xTaskCreate(button_task_entry, "button_task", 128 * 4, NULL,  3 | portPRIVILEGE_BIT, button_taskHandle);
    /* creation of io_generic_task */
    xTaskCreate(io_generic_task_entry, "io_generic_task", 128 * 4, NULL,  2 | portPRIVILEGE_BIT, io_generic_taskHandle);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct =
    { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct =
    { 0 };

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{

    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART2_Init 2 */

    /* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *pvParameters)
{
    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END 5 */
}

/**
 * @brief Function implementing the spinner_task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_spinner_task_entry */
void spinner_task_entry(void *pvParameters)
{
    volatile uint32_t spinner_period_ms = 400;
    spinner_init(&spinner_queue_handle);
    /* Infinite loop */
    for (;;)
    {
        if(uxQueueMessagesWaiting(spinner_queue_handle) != 0)
        {
            xQueueReceive(spinner_queue_handle, &spinner_period_ms,0);
        }
        spinner_run();
        vTaskDelay(spinner_period_ms);
    }
    vTaskDelay(0);
}

/**
 * @brief Function implementing the button_task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_button_task_entry */
void button_task_entry(void *pvParameters)
{
    volatile uint8_t button_read_period_ms = 1;
    button_controler_init();
    /* Infinite loop */
    for (;;)
    {
        button_controler_run();
        vTaskDelay(button_read_period_ms / portTICK_RATE_MS);
    }
    vTaskDelay(0);
}

/**
 * @brief Function implementing the io_generic_task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_io_configurate_task_entry */
void io_generic_task_entry(void *pvParameters)
{
    io_configurate();
    /* Infinite loop */
    for (;;)
    {
        io_generic_run();
    }
    vTaskDelay(0);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
