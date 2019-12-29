#include <stdio.h>
#include <stdlib.h>

#include <borealis.hpp>
#include <string>


std::vector<std::string> NOTIFICATIONS = {
    "You have cool hair",
    "I like your shoes",
    "borealis is powered by nanovg",
    "The Triforce is an inside job",
    "Pozznx will trigger in one day and twelve hours",
    "Aurora Borealis? At this time of day, at this time of year, in this part of the gaming market, located entirely within your Switch?!",
    "May I see it?",
    "Hmm, Steamed Hams!"
};

int main(int argc, char* argv[])
{
    // Init the app
    brls::Logger::setLogLevel(brls::LogLevel::DEBUG);

    if (!brls::Application::init())
    {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }

    // Create a sample view
    brls::TabFrame* rootFrame = new brls::TabFrame();
    rootFrame->setTitle("Borealis Example App");
    rootFrame->setIcon(ASSET("icon/borealis.jpg"));

    brls::List* testList = new brls::List();

    brls::ListItem* dialogItem = new brls::ListItem("Open a dialog");
    dialogItem->setClickListener([](brls::View* view) {
        brls::Dialog* dialog = new brls::Dialog("Warning: PozzNX will wipe all data on your Switch and render it inoperable, do you want to proceed?");

        brls::EventListener closeListener = [dialog](brls::View* view) {
            dialog->close();
            brls::Application::notify("Running PozzNX...");
        };

        dialog->addButton("Continue", closeListener);
        dialog->addButton("Continue", closeListener);
        dialog->addButton("Continue", closeListener);

        dialog->setCancelable(false);

        dialog->open();
    });

    brls::ListItem* notificationItem = new brls::ListItem("Post a random notification");
    notificationItem->setClickListener([](brls::View* view) {
        std::string notification = NOTIFICATIONS[std::rand() % NOTIFICATIONS.size()];
        brls::Application::notify(notification);
    });

    brls::ListItem* themeItem = new brls::ListItem("TV Resolution");
    themeItem->setValue("Automatic");

    brls::ListItem* jankItem = new brls::ListItem("User Interface Jank", "Some people believe homebrews to have a jank user interface. Set to Minimal to have a native look and feel, set to Maximal to have a SX OS look and feel.");
    jankItem->setValue("Minimal");

    brls::ListItem* crashItem = new brls::ListItem("Divide by 0", "Can the Switch do it?");
    crashItem->setClickListener([](brls::View* view) { brls::Application::crash("The software was closed because an error occured:\nSIGABRT (signal 6)"); });

    brls::ListItem* popupItem = new brls::ListItem("Open popup");


    brls::SelectListItem* layerSelectItem = new brls::SelectListItem("Select Layer", { "Layer 1", "Layer 2" });

    testList->addView(dialogItem);
    testList->addView(notificationItem);
    testList->addView(themeItem);
    testList->addView(jankItem);
    testList->addView(crashItem);
    testList->addView(popupItem);

    brls::Label* testLabel = new brls::Label(brls::LabelStyle::REGULAR, "For more information about how to use Nintendo Switch and its features, please refer to the Nintendo Support Website on your smart device or PC.", true);
    testList->addView(testLabel);

    brls::LayerView* testLayers = new brls::LayerView();
    brls::List* layerList1      = new brls::List();
    brls::List* layerList2      = new brls::List();

    layerList1->addView(new brls::Header("Layer 1", false));
    layerList1->addView(new brls::ListItem("Item 1"));
    layerList1->addView(new brls::ListItem("Item 2"));
    layerList1->addView(new brls::ListItem("Item 3"));

    layerList2->addView(new brls::Header("Layer 2", false));
    layerList2->addView(new brls::ListItem("Item 1"));
    layerList2->addView(new brls::ListItem("Item 2"));
    layerList2->addView(new brls::ListItem("Item 3"));

    testLayers->addLayer(layerList1);
    testLayers->addLayer(layerList2);

    layerSelectItem->setListener([=](size_t selection) {
        testLayers->changeLayer(selection);
    });

    testList->addView(layerSelectItem);

    rootFrame->addTab("First tab", testList);
    rootFrame->addTab("Second tab", testLayers);
    rootFrame->addSeparator();
    rootFrame->addTab("Third tab", new brls::Rectangle(nvgRGB(255, 0, 0)));
    rootFrame->addTab("Fourth tab", new brls::Rectangle(nvgRGB(0, 255, 0)));

    // Add the root view to the stack
    brls::Application::pushView(rootFrame);

    // Run the app
    while (brls::Application::mainLoop())
        ;

    // Exit
    return EXIT_SUCCESS;
}
