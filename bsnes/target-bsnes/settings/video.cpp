auto VideoSettings::create() -> void {
  setCollapsible();
  setVisible(false);

  colorAdjustmentLabel.setFont(Font().setBold()).setText("颜色调整");
  colorLayout.setSize({3, 3});
  colorLayout.column(0).setAlignment(1.0);
  luminanceLabel.setText("亮度值:");
  luminanceValue.setAlignment(0.5);
  luminanceSlider.setLength(101).setPosition(settings.video.luminance).onChange([&] {
    string value = {luminanceSlider.position(), "%"};
    settings.video.luminance = value.natural();
    emulator->configure("Video/Luminance", settings.video.luminance);
    luminanceValue.setText(value);
  }).doChange();
  saturationLabel.setText("饱和度:");
  saturationValue.setAlignment(0.5);
  saturationSlider.setLength(201).setPosition(settings.video.saturation).onChange([&] {
    string value = {saturationSlider.position(), "%"};
    settings.video.saturation = value.natural();
    emulator->configure("Video/Saturation", settings.video.saturation);
    saturationValue.setText(value);
  }).doChange();
  gammaLabel.setText("伽玛值:");
  gammaValue.setAlignment(0.5);
  gammaSlider.setLength(101).setPosition(settings.video.gamma - 100).onChange([&] {
    string value = {100 + gammaSlider.position(), "%"};
    settings.video.gamma = value.natural();
    emulator->configure("Video/Gamma", settings.video.gamma);
    gammaValue.setText(value);
  }).doChange();

  dimmingOption.setText("Dim video when idle").setToolTip(
    "Darkens the video to indicate that the emulation is not running."
  ).setChecked(settings.video.dimming).onToggle([&] {
    settings.video.dimming = dimmingOption.checked();
  });

  snowOption.setText("Draw snow effect when idle").setChecked(settings.video.snow).onToggle([&] {
    settings.video.snow = snowOption.checked();
    presentation.updateProgramIcon();
  });
}
